#!/usr/bin/env python3
"""
SunnyPilot地図スタイルを白黒（グレースケール）に変換するスクリプト
"""

import json
import re
import os
from pathlib import Path

def rgb_to_gray(rgb_str):
    """RGB色をグレースケールに変換"""
    # RGB(r,g,b)形式の処理
    rgb_match = re.search(r'rgb\(\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*\)', rgb_str)
    if rgb_match:
        r, g, b = map(int, rgb_match.groups())
        gray = int(0.299 * r + 0.587 * g + 0.114 * b)
        return f"rgb({gray}, {gray}, {gray})"
    
    # RGBA(r,g,b,a)形式の処理
    rgba_match = re.search(r'rgba\(\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*([\d.]+)\s*\)', rgb_str)
    if rgba_match:
        r, g, b, a = rgba_match.groups()
        r, g, b = map(int, [r, g, b])
        gray = int(0.299 * r + 0.587 * g + 0.114 * b)
        return f"rgba({gray}, {gray}, {gray}, {a})"
    
    return rgb_str

def hex_to_gray(hex_str):
    """HEX色をグレースケールに変換"""
    if not hex_str.startswith('#'):
        return hex_str
    
    try:
        if len(hex_str) == 4:  # #RGB形式
            r = int(hex_str[1], 16) * 17
            g = int(hex_str[2], 16) * 17
            b = int(hex_str[3], 16) * 17
        elif len(hex_str) == 7:  # #RRGGBB形式
            r = int(hex_str[1:3], 16)
            g = int(hex_str[3:5], 16)
            b = int(hex_str[5:7], 16)
        else:
            return hex_str
        
        gray = int(0.299 * r + 0.587 * g + 0.114 * b)
        return f"#{gray:02x}{gray:02x}{gray:02x}"
    except:
        return hex_str

def hsl_to_gray(hsl_str):
    """HSL色をグレースケールに変換"""
    # HSL色は明度(Lightness)を使用してグレースケール化
    hsl_match = re.search(r'hsl\(\s*([\d.]+)\s*,\s*([\d.%]+)\s*,\s*([\d.%]+)\s*\)', hsl_str)
    if hsl_match:
        hue, saturation, lightness = hsl_match.groups()
        lightness = lightness.replace('%', '')
        try:
            l_val = float(lightness)
            # 明度を直接グレースケール値として使用
            if '%' in hsl_match.group():
                gray_val = int(l_val * 2.55)  # %を0-255に変換
            else:
                gray_val = int(l_val * 255 / 100) if l_val <= 1.0 else int(l_val * 2.55)
            gray_val = max(0, min(255, gray_val))  # 0-255に制限
            return f"rgb({gray_val}, {gray_val}, {gray_val})"
        except:
            pass
    
    hsla_match = re.search(r'hsla\(\s*([\d.]+)\s*,\s*([\d.%]+)\s*,\s*([\d.%]+)\s*,\s*([\d.]+)\s*\)', hsl_str)
    if hsla_match:
        hue, saturation, lightness, alpha = hsla_match.groups()
        lightness = lightness.replace('%', '')
        try:
            l_val = float(lightness)
            if '%' in lightness:
                gray_val = int(l_val * 2.55)
            else:
                gray_val = int(l_val * 255 / 100) if l_val <= 1.0 else int(l_val * 2.55)
            gray_val = max(0, min(255, gray_val))  # 0-255に制限
            return f"rgba({gray_val}, {gray_val}, {gray_val}, {alpha})"
        except:
            pass
    
    return hsl_str

def convert_color_to_grayscale(color):
    """任意の色をグレースケールに変換"""
    if isinstance(color, str):
        color = color.strip()
        
        # RGB/RGBA形式
        if color.startswith('rgb'):
            return rgb_to_gray(color)
        
        # HEX形式
        elif color.startswith('#'):
            return hex_to_gray(color)
        
        # HSL/HSLA形式
        elif color.startswith('hsl'):
            return hsl_to_gray(color)
        
        # 名前付きカラーのマッピング
        color_map = {
            'black': '#000000',
            'white': '#ffffff',
            'red': '#808080',
            'green': '#808080', 
            'blue': '#808080',
            'yellow': '#c0c0c0',
            'cyan': '#a0a0a0',
            'magenta': '#808080',
            'transparent': 'transparent'
        }
        
        if color.lower() in color_map:
            return color_map[color.lower()]
    
    return color

def convert_layer_to_grayscale(layer):
    """レイヤーの色設定をグレースケールに変換"""
    if 'paint' in layer:
        paint = layer['paint']
        
        # 塗りつぶし色
        if 'fill-color' in paint:
            if isinstance(paint['fill-color'], str):
                paint['fill-color'] = convert_color_to_grayscale(paint['fill-color'])
            elif isinstance(paint['fill-color'], dict):
                # ストップやケース式の処理
                if 'stops' in paint['fill-color']:
                    for stop in paint['fill-color']['stops']:
                        if len(stop) >= 2:
                            stop[1] = convert_color_to_grayscale(stop[1])
        
        # アウトライン色
        if 'fill-outline-color' in paint:
            paint['fill-outline-color'] = convert_color_to_grayscale(paint['fill-outline-color'])
        
        # 線の色
        if 'line-color' in paint:
            if isinstance(paint['line-color'], str):
                paint['line-color'] = convert_color_to_grayscale(paint['line-color'])
            elif isinstance(paint['line-color'], dict):
                if 'stops' in paint['line-color']:
                    for stop in paint['line-color']['stops']:
                        if len(stop) >= 2:
                            stop[1] = convert_color_to_grayscale(stop[1])
        
        # テキスト色
        if 'text-color' in paint:
            paint['text-color'] = convert_color_to_grayscale(paint['text-color'])
        
        # テキストハロー色
        if 'text-halo-color' in paint:
            paint['text-halo-color'] = convert_color_to_grayscale(paint['text-halo-color'])
        
        # 背景色
        if 'background-color' in paint:
            paint['background-color'] = convert_color_to_grayscale(paint['background-color'])
        
        # アイコン色
        if 'icon-color' in paint:
            paint['icon-color'] = convert_color_to_grayscale(paint['icon-color'])
        
        # シンボル色
        if 'symbol-color' in paint:
            paint['symbol-color'] = convert_color_to_grayscale(paint['symbol-color'])

def convert_style_to_grayscale_auto(style_path):
    """style.jsonを白黒に変換（自動モード - 確認なし）"""
    
    # バックアップを作成
    backup_path = style_path.replace('.json', '_backup.json')
    if not os.path.exists(backup_path):
        print(f"バックアップを作成中: {backup_path}")
        with open(style_path, 'r', encoding='utf-8') as f:
            backup_content = f.read()
        with open(backup_path, 'w', encoding='utf-8') as f:
            f.write(backup_content)
    
    # 既存のstyle.jsonを読み込み
    with open(style_path, 'r', encoding='utf-8') as f:
        style = json.load(f)
    
    print("地図スタイルを白黒に変換中...")
    
    # スタイル名を変更
    style['name'] = 'OSMstyle-Grayscale'
    
    # 各レイヤーを処理
    for layer in style.get('layers', []):
        convert_layer_to_grayscale(layer)
    
    # 白黒バージョンを保存
    grayscale_path = style_path.replace('.json', '_grayscale.json')
    with open(grayscale_path, 'w', encoding='utf-8') as f:
        json.dump(style, f, indent=2, ensure_ascii=False)
    
    print(f"白黒スタイルを保存しました: {grayscale_path}")

def convert_style_to_grayscale(style_path):
    """style.jsonを白黒に変換"""
    
    # バックアップを作成
    backup_path = style_path.replace('.json', '_backup.json')
    if not os.path.exists(backup_path):
        print(f"バックアップを作成中: {backup_path}")
        with open(style_path, 'r', encoding='utf-8') as f:
            backup_content = f.read()
        with open(backup_path, 'w', encoding='utf-8') as f:
            f.write(backup_content)
    
    # 既存のstyle.jsonを読み込み
    with open(style_path, 'r', encoding='utf-8') as f:
        style = json.load(f)
    
    print("地図スタイルを白黒に変換中...")
    
    # スタイル名を変更
    style['name'] = 'OSMstyle-Grayscale'
    
    # 各レイヤーを処理
    for layer in style.get('layers', []):
        convert_layer_to_grayscale(layer)
    
    # 白黒バージョンを保存
    grayscale_path = style_path.replace('.json', '_grayscale.json')
    with open(grayscale_path, 'w', encoding='utf-8') as f:
        json.dump(style, f, indent=2, ensure_ascii=False)
    
    print(f"白黒スタイルを保存しました: {grayscale_path}")
    
    # 元のファイルを白黒版で置き換えるか確認
    replace = input("元のstyle.jsonを白黒版で置き換えますか？ (y/N): ").lower().strip()
    if replace == 'y' or replace == 'yes':
        with open(style_path, 'w', encoding='utf-8') as f:
            json.dump(style, f, indent=2, ensure_ascii=False)
        print(f"style.jsonを白黒版に更新しました")
        print(f"元のファイルは {backup_path} にバックアップされています")
    else:
        print(f"白黒版は {grayscale_path} に保存されました")
        print("必要に応じて手動でstyle.jsonと置き換えてください")

def restore_original_style(style_path):
    """バックアップから元のスタイルを復元"""
    backup_path = style_path.replace('.json', '_backup.json')
    
    if os.path.exists(backup_path):
        with open(backup_path, 'r', encoding='utf-8') as f:
            original_content = f.read()
        with open(style_path, 'w', encoding='utf-8') as f:
            f.write(original_content)
        print("元のカラースタイルを復元しました")
    else:
        print("バックアップファイルが見つかりません")

if __name__ == "__main__":
    import sys
    
    # SunnyPilotのstyle.jsonパス
    script_dir = Path(__file__).parent
    style_path = script_dir / "selfdrive" / "navd" / "style.json"
    
    if not style_path.exists():
        print(f"エラー: style.jsonが見つかりません: {style_path}")
        print("このスクリプトをSunnyPilotのルートディレクトリで実行してください")
        exit(1)
    
    # 自動変換オプション
    if len(sys.argv) > 1 and sys.argv[1] == "--auto-convert":
        print("自動モード: グレースケール版を作成中...")
        convert_style_to_grayscale_auto(str(style_path))
        exit(0)
    
    print("=== SunnyPilot地図スタイル変換ツール ===")
    print("1. カラー地図を白黒に変換")
    print("2. 元のカラー地図を復元")
    
    choice = input("選択してください (1/2): ").strip()
    
    if choice == "1":
        convert_style_to_grayscale(str(style_path))
    elif choice == "2":
        restore_original_style(str(style_path))
    else:
        print("無効な選択です")
    
    print("\n変更を適用するにはSunnyPilotを再起動してください")
