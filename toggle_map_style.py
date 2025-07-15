#!/usr/bin/env python3
"""
SunnyPilot地図スタイル簡単切り替えスクリプト
"""

import os
import json
from pathlib import Path
from openpilot.common.params import Params

def get_current_style():
    """現在の地図スタイル（カラー/グレースケール）を確認"""
    try:
        params = Params()
        use_grayscale = params.get("MaptilerUseGrayscale", encoding='utf-8')
        return "グレースケール" if use_grayscale == "1" else "カラー"
    except:
        return "不明"

def toggle_map_style():
    """地図スタイルを切り替え（カラー ↔ グレースケール）"""
    try:
        params = Params()
        current = params.get("MaptilerUseGrayscale", encoding='utf-8')
        
        if current == "1":
            # グレースケール → カラーに切り替え
            params.put("MaptilerUseGrayscale", "0")
            restore_color_style()
            print("✅ 地図スタイルをカラーに切り替えました")
            return "カラー"
        else:
            # カラー → グレースケールに切り替え
            params.put("MaptilerUseGrayscale", "1")
            apply_grayscale_style()
            print("✅ 地図スタイルをグレースケールに切り替えました")
            return "グレースケール"
    except Exception as e:
        print(f"❌ エラー: {e}")
        return "エラー"

def apply_grayscale_style():
    """グレースケールスタイルを適用"""
    script_dir = Path(__file__).parent
    style_path = script_dir / "selfdrive" / "navd" / "style.json"
    grayscale_path = script_dir / "selfdrive" / "navd" / "style_grayscale.json"
    
    # グレースケール版が存在しない場合は作成
    if not grayscale_path.exists():
        print("グレースケール版を作成中...")
        os.system(f"python {script_dir}/convert_map_to_grayscale.py --auto-convert")
    
    # グレースケール版をコピー
    if grayscale_path.exists():
        with open(grayscale_path, 'r', encoding='utf-8') as f:
            grayscale_content = f.read()
        with open(style_path, 'w', encoding='utf-8') as f:
            f.write(grayscale_content)

def restore_color_style():
    """カラースタイルを復元"""
    script_dir = Path(__file__).parent
    style_path = script_dir / "selfdrive" / "navd" / "style.json"
    backup_path = script_dir / "selfdrive" / "navd" / "style_backup.json"
    
    if backup_path.exists():
        with open(backup_path, 'r', encoding='utf-8') as f:
            backup_content = f.read()
        with open(style_path, 'w', encoding='utf-8') as f:
            f.write(backup_content)
    else:
        print("⚠️  バックアップファイルが見つかりません")

def check_maptiler_setup():
    """Maptiler設定状況をチェック"""
    try:
        params = Params()
        api_key = params.get("MaptilerApiKey", encoding='utf-8')
        if api_key and len(api_key) > 10:
            return True, api_key[:8] + "..."
        else:
            return False, None
    except:
        return False, None

if __name__ == "__main__":
    print("=== SunnyPilot地図スタイル切り替えツール ===")
    print()
    
    # Maptiler設定チェック
    has_key, key_preview = check_maptiler_setup()
    if has_key:
        print(f"✅ MaptilerAPIキー: {key_preview}")
    else:
        print("❌ MaptilerAPIキーが設定されていません")
        print("   先に set_maptiler_key.py でAPIキーを設定してください")
        print()
    
    # 現在のスタイル表示
    current_style = get_current_style()
    print(f"現在の地図スタイル: {current_style}")
    print()
    
    if has_key:
        # スタイル切り替え
        print("地図スタイルを切り替えますか？")
        print("1. スタイルを切り替える")
        print("2. 現在の設定を確認のみ")
        print()
        
        choice = input("選択してください (1/2): ").strip()
        
        if choice == "1":
            print()
            new_style = toggle_map_style()
            print()
            print("🔄 SunnyPilotを再起動して変更を適用してください")
        else:
            print("設定確認のみで終了します")
    else:
        print("APIキーを設定してから再度実行してください")
