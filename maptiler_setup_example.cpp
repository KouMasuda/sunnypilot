// Maptiler用MapRenderer設定の例
// このコードはlibmaprender.soのソースコードに統合する必要があります

#include <QMapLibre/Settings>
#include "common/params.h"

QMapLibre::Settings createMaptilerSettings() {
  // Maptiler Provider を設定
  QMapLibre::Settings settings(QMapLibre::Settings::MapTilerProvider);
  
  // APIキーを Params から取得
  Params params;
  std::string api_key = params.get("MaptilerApiKey");
  
  if (!api_key.empty()) {
    // Maptiler設定
    settings.setApiKey(QString::fromStdString(api_key));
    settings.setApiBaseUrl("https://api.maptiler.com");
    
    // 地図の基本設定
    settings.setCacheDatabasePath("/data/media/0/maptiler_cache.db");
    settings.setCacheDatabaseMaximumSize(50 * 1024 * 1024); // 50MB
    
    // デフォルト座標とズーム（日本）
    settings.setDefaultCoordinate({35.6762, 139.6503}); // 東京
    settings.setDefaultZoom(10.0);
    
    printf("Maptiler APIキーが設定されました: %.8s...\n", api_key.c_str());
  } else {
    printf("警告: MaptilerApiKeyが設定されていません\n");
    // デフォルト設定を使用
    settings = QMapLibre::Settings(QMapLibre::Settings::NoProvider);
  }
  
  return settings;
}

// map_renderer_init関数の例
extern "C" void* map_renderer_init(char *maps_host, char *token) {
  QMapLibre::Settings settings = createMaptilerSettings();
  
  // 引数でAPIキーとホストが渡された場合は上書き
  if (token && strlen(token) > 0) {
    settings.setApiKey(QString(token));
  }
  if (maps_host && strlen(maps_host) > 0) {
    settings.setApiBaseUrl(QString(maps_host));
  }
  
  // MapRendererインスタンスを作成（実際の実装に依存）
  auto* renderer = new MapRenderer(settings);
  return renderer;
}
