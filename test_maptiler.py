#!/usr/bin/env python3
"""
SunnyPilotでMaptiler地図表示をテストするスクリプト
"""

import os
import sys
import time
from pathlib import Path

# SunnyPilotのパスを追加
BASEDIR = Path(__file__).parent
sys.path.append(str(BASEDIR))

from openpilot.common.params import Params
from openpilot.selfdrive.navd.map_renderer import create_maptiler_renderer, wait_ready, get_image

def test_maptiler_map():
    """Maptiler地図表示をテスト"""
    
    print("=== SunnyPilot Maptiler地図表示テスト ===")
    
    # APIキーの確認
    params = Params()
    api_key = params.get("MaptilerApiKey", encoding='utf-8')
    
    if not api_key:
        print("エラー: MaptilerApiKeyが設定されていません")
        print("1. まず set_maptiler_key.py を実行してAPIキーを設定してください")
        return False
    
    print(f"APIキー確認済み: {api_key[:8]}...")
    
    try:
        print("地図レンダラーを初期化中...")
        ffi, lib, renderer = create_maptiler_renderer()
        
        print("地図の読み込み待機中...")
        wait_ready(lib, renderer, timeout=30)  # 30秒タイムアウト
        
        # テスト位置（東京）
        test_positions = [
            (35.6762, 139.6503, 0),    # 東京駅
            (35.6895, 139.6917, 0),   # 新宿駅  
            (35.7090, 139.7319, 0),   # 池袋駅
        ]
        
        for i, (lat, lon, bearing) in enumerate(test_positions):
            print(f"位置 {i+1}: 緯度={lat}, 経度={lon}")
            
            # 位置を更新
            lib.map_renderer_update_position(renderer, lat, lon, bearing)
            lib.map_renderer_update(renderer)
            
            # 地図の準備を待機
            wait_ready(lib, renderer, timeout=10)
            
            # 地図画像を取得
            image = get_image(lib, renderer)
            print(f"地図画像を取得しました: {image.shape}")
            
            # 画像を保存（オプション）
            if 'numpy' in sys.modules:
                import numpy as np
                from PIL import Image
                img = Image.fromarray(image.astype(np.uint8))
                img.save(f"/tmp/maptiler_test_{i+1}.png")
                print(f"画像を保存しました: /tmp/maptiler_test_{i+1}.png")
        
        print("✅ Maptiler地図表示テスト成功！")
        return True
        
    except Exception as e:
        print(f"❌ エラー: {str(e)}")
        return False

def check_requirements():
    """必要な設定とファイルを確認"""
    print("=== 設定確認 ===")
    
    # libmaprender.soの存在確認
    lib_path = Path(BASEDIR) / "selfdrive" / "navd" / "libmaprender.so"
    if lib_path.exists():
        print(f"✅ libmaprender.so: {lib_path}")
    else:
        print(f"❌ libmaprender.so が見つかりません: {lib_path}")
        return False
    
    # style.jsonの確認
    style_path = Path(BASEDIR) / "selfdrive" / "navd" / "style.json"
    if style_path.exists():
        print(f"✅ style.json: {style_path}")
    else:
        print(f"❌ style.json が見つかりません: {style_path}")
        return False
    
    # APIキー確認
    params = Params()
    api_key = params.get("MaptilerApiKey", encoding='utf-8')
    if api_key:
        print(f"✅ MaptilerApiKey: {api_key[:8]}...")
    else:
        print("❌ MaptilerApiKey が設定されていません")
        return False
    
    return True

if __name__ == "__main__":
    print("SunnyPilot Maptiler設定とテスト")
    print("-" * 50)
    
    if not check_requirements():
        print("\n必要な設定が不足しています。")
        print("1. APIキーを設定: python set_maptiler_key.py")
        print("2. libmaprender.soをビルド")
        sys.exit(1)
    
    print("\n設定確認完了。地図表示テストを開始...")
    success = test_maptiler_map()
    
    if success:
        print("\n🎉 Maptiler地図がSunnyPilotで正常に動作しています！")
    else:
        print("\n💡 トラブルシューティング:")
        print("- APIキーが正しいことを確認")
        print("- インターネット接続を確認")
        print("- libmaprender.soが最新であることを確認")
