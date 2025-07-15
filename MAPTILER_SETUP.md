# SunnyPilot Maptiler地図表示設定ガイド

SunnyPilotのsunny-mapブランチでMaptilerの地図を表示するための設定手順です。

## 必要なもの

1. **Maptiler APIキー**
   - https://www.maptiler.com/ でアカウント作成
   - 無料プランで月100,000リクエストまで利用可能

2. **SunnyPilot (sunny-mapブランチ)**
   - MapLibre Native Qt統合済み
   - libmaprender.soビルド済み

## 設定手順

### 1. Maptiler APIキーの設定

```bash
# APIキー設定スクリプトを編集
nano set_maptiler_key.py

# YOUR_MAPTILER_API_KEY_HERE を実際のAPIキーに置換

# APIキーを設定
python set_maptiler_key.py
```

### 2. 設定確認とテスト実行

```bash
# 設定確認とテストを実行
python test_maptiler.py
```

### 3. SunnyPilotでの地図表示

設定が完了すると、SunnyPilotの地図表示が自動的にMaptilerを使用するようになります。

## 技術的詳細

### ファイル構成

- `set_maptiler_key.py` - APIキー設定スクリプト
- `test_maptiler.py` - 地図表示テストスクリプト  
- `maptiler_setup_example.cpp` - C++設定例
- `selfdrive/navd/map_renderer.py` - Python地図レンダラー（修正済み）
- `selfdrive/navd/style.json` - Maptilerスタイル設定
- `third_party/maplibre-native-qt/` - MapLibre Native Qt

### MapLibre Settings設定

C++側でのMaptiler設定：

```cpp
QMapLibre::Settings settings(QMapLibre::Settings::MapTilerProvider);
settings.setApiKey("YOUR_API_KEY");
settings.setApiBaseUrl("https://api.maptiler.com");
```

### Python側での設定

```python
from openpilot.selfdrive.navd.map_renderer import create_maptiler_renderer

# Maptiler設定でレンダラー作成
ffi, lib, renderer = create_maptiler_renderer()
```

## トラブルシューティング

### よくある問題

1. **地図が表示されない**
   - APIキーが正しく設定されているか確認
   - インターネット接続確認
   - ログで認証エラーがないか確認

2. **Performance issues**
   - キャッシュディレクトリ(`/data/media/0/maptiler_cache.db`)の容量確認
   - APIレート制限の確認

3. **Style issues**
   - `style.json`の`{key}`プレースホルダーが正しく置換されているか確認

### ログ確認

```bash
# SunnyPilotログでMaptiler関連エラー確認
tail -f /data/media/0/realdata/logs/swaglog.txt | grep -i maptiler
```

## 地図スタイルのカスタマイズ

`selfdrive/navd/style.json`を編集して地図の外観をカスタマイズできます：

- 色テーマの変更
- レイヤーの表示/非表示
- フォントの変更
- アイコンの変更

詳細は [Mapbox Style Specification](https://docs.mapbox.com/mapbox-gl-js/style-spec/) を参照してください。

## ライセンスと利用規約

- Maptilerの利用規約に従って使用してください
- APIキーは秘密情報として適切に管理してください
- 商用利用の場合は適切なプランを選択してください

## サポート

問題が発生した場合：

1. このREADMEのトラブルシューティングセクションを確認
2. SunnyPilot GitHubのIssueで報告
3. Maptilerの公式ドキュメントを参照

---

**注意**: このガイドはsunny-mapブランチ専用です。他のブランチでは動作しない可能性があります。
