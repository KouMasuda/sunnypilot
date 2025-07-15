#!/usr/bin/env python3
"""
SunnyPilotでMaptiler APIキーを設定するスクリプト
"""

import os
from pathlib import Path
from openpilot.common.params import Params

def set_maptiler_key(api_key):
    """Maptiler APIキーを設定"""
    params = Params()
    params.put("MaptilerApiKey", api_key)
    print(f"Maptiler APIキーが設定されました: {api_key[:8]}...")

def set_map_style(use_grayscale=False):
    """地図スタイルを設定（カラー/グレースケール）"""
    params = Params()
    if use_grayscale:
        params.put("MaptilerUseGrayscale", "1")
        print("地図スタイル: 白黒（グレースケール）")
    else:
        params.put("MaptilerUseGrayscale", "0") 
        print("地図スタイル: カラー")

def convert_to_grayscale():
    """地図スタイルファイルを白黒に変換"""
    script_dir = Path(__file__).parent
    convert_script = script_dir / "convert_map_to_grayscale.py"
    
    if convert_script.exists():
        print("地図スタイル変換スクリプトを実行中...")
        os.system(f"python {convert_script}")
    else:
        print("地図スタイル変換スクリプトが見つかりません")

if __name__ == "__main__":
    print("=== SunnyPilot Maptiler設定ツール ===")
    print()
    
    # ここにあなたのMaptiler APIキーを入力してください
    # 以下の手順でAPIキーを取得してください：
    # 1. https://www.maptiler.com/ でアカウント作成
    # 2. ダッシュボードからAPIキーを取得
    # 3. 下の行を実際のキーで置き換え
    api_key = "YOUR_MAPTILER_API_KEY_HERE"
    
    if api_key == "YOUR_MAPTILER_API_KEY_HERE":
        print("エラー: 実際のMaptiler APIキーを設定してください")
        print("1. https://www.maptiler.com/ でアカウント作成")
        print("2. APIキーを取得")
        print("3. このスクリプトのapi_key変数を更新")
        print()
    else:
        set_maptiler_key(api_key)
        print()
    
    # 地図スタイル設定
    print("地図スタイルの設定:")
    print("1. カラー地図")
    print("2. 白黒地図 (グレースケール)")
    print("3. style.jsonを直接変換")
    
    choice = input("選択してください (1/2/3): ").strip()
    
    if choice == "1":
        set_map_style(use_grayscale=False)
        print("カラー地図に設定しました")
    elif choice == "2":
        set_map_style(use_grayscale=True)
        print("白黒地図に設定しました")
        print("注意: この設定を有効にするには、style.jsonファイルも変換する必要があります")
        print("オプション3を選択してstyle.jsonを変換してください")
    elif choice == "3":
        convert_to_grayscale()
    else:
        print("設定をスキップしました")
    
    print("\n設定が完了しました。SunnyPilotを再起動して変更を適用してください。")
