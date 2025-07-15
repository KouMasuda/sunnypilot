# SunnyPilot Maptiler地図表示 設定手順

## 概要
SunnyPilotでMaptilerの地図表示を有効にし、カラー地図と白黒地図を簡単に切り替えるためのガイドです。

## 必要な準備

### 1. Maptiler APIキーの取得
1. [Maptiler](https://www.maptiler.com/) でアカウントを作成
2. ダッシュボードから無料のAPIキーを取得
3. APIキーをコピー（例：`pk.abc123def456...`）

## 設定手順

### ステップ1: APIキーの設定
```bash
cd /home/kou/sunnypilot
python set_maptiler_key.py
```

**重要**: 初回実行前に`set_maptiler_key.py`を編集してAPIキーを設定してください：
```python
api_key = "あなたの実際のAPIキー"
```

### ステップ2: 地図スタイルの切り替え（簡単方法）
```bash
python toggle_map_style.py
```
このスクリプトで：
- 現在の設定状況を確認
- ワンクリックでカラー ↔ グレースケール切り替え
- 自動的にファイル変換も実行

### ステップ3: SunnyPilotの再起動
設定完了後、SunnyPilotを再起動して変更を適用

## 利用可能なスクリプト

### 🚀 推奨：簡単切り替えツール
```bash
python toggle_map_style.py
```
- **最も簡単な方法**
- 現在の設定を確認
- ワンクリックで切り替え

### ⚙️ 詳細設定ツール
```bash
python set_maptiler_key.py
```
- APIキー設定
- 詳細なスタイル設定
- 初回設定時に推奨

### 🔧 手動変換ツール
```bash
python convert_map_to_grayscale.py
```
- style.jsonファイルの直接変換
- バックアップと復元
- 詳細なカスタマイズ

## ファイル構成

```
/home/kou/sunnypilot/
├── toggle_map_style.py             # 🚀 簡単切り替えツール（推奨）
├── set_maptiler_key.py              # APIキー設定とスタイル切り替え
├── convert_map_to_grayscale.py      # グレースケール変換スクリプト
├── MAPTILER_使用手順.md             # このガイド
├── selfdrive/navd/style.json        # 地図スタイル設定ファイル
├── selfdrive/navd/style_backup.json # バックアップファイル（自動作成）
└── selfdrive/navd/style_grayscale.json # グレースケール版（自動作成）
```

## 使用例

### 初回設定
```bash
# 1. APIキーを設定
python set_maptiler_key.py

# 2. 地図スタイルを確認・切り替え  
python toggle_map_style.py

# 3. SunnyPilot再起動
```

### 日常的な切り替え
```bash
# 地図スタイルをサッと切り替え
python toggle_map_style.py
```

## トラブルシューティング

### 地図が表示されない場合
1. APIキーが正しく設定されているか確認
2. インターネット接続を確認
3. SunnyPilotを完全に再起動

### 白黒地図が反映されない場合
1. `toggle_map_style.py`で自動切り替えを試す
2. SunnyPilotを再起動

### 元の地図に戻したい場合
```bash
python toggle_map_style.py
# 現在グレースケールならカラーに自動切り替え
```

または手動で：
```bash
python convert_map_to_grayscale.py
# 選択肢で「2」を選択してバックアップから復元
```

## 技術詳細

### サポートされる色形式
- HEX色: `#ff0000` → `#808080`
- RGB色: `rgb(255,0,0)` → `rgb(128,128,128)`
- RGBA色: `rgba(255,0,0,0.5)` → `rgba(128,128,128,0.5)`
- HSL色: `hsl(120,50%,50%)` → `rgb(127,127,127)`
- 名前付き色: `red` → `#808080`

### グレースケール変換アルゴリズム
標準的な輝度計算式を使用：
```
Gray = 0.299 * R + 0.587 * G + 0.114 * B
```

## 注意事項
- バックアップファイルを削除しないでください
- style.jsonを手動で編集する場合は事前にバックアップを作成
- APIキーは他人と共有しないでください

## サポート
問題が発生した場合は、SunnyPilotのコミュニティやドキュメントを参照してください。
