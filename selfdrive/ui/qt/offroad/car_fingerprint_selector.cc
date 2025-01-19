#include "selfdrive/ui/qt/offroad/car_fingerprint_selector.h"
#include "selfdrive/common/params.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

CarFingerprintSelector::CarFingerprintSelector(QWidget *parent) : QWidget(parent) {
  QVBoxLayout *layout = new QVBoxLayout(this);

  fingerprint_list = new QListWidget(this);
  layout->addWidget(fingerprint_list);

  // 加载车型指纹列表
  loadFingerprints();

  QPushButton *confirm_btn = new QPushButton("确认选择", this);
  layout->addWidget(confirm_btn);

  connect(confirm_btn, &QPushButton::clicked, [=]() {
    QListWidgetItem *selected_item = fingerprint_list->currentItem();
    if (selected_item) {
      QString selected_fingerprint = selected_item->text();
      Params().put("ForceCarFingerprint", selected_fingerprint.toStdString());
      close();
    }
  });
}

void CarFingerprintSelector::loadFingerprints() {
  QFile file("../selfdrive/data/fingerprints.json");
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning("无法打开指纹文件");
    return;
  }

  QByteArray data = file.readAll();
  QJsonDocument doc = QJsonDocument::fromJson(data);
  QJsonObject obj = doc.object();

  for (const QString &key : obj.keys()) {
    fingerprint_list->addItem(key);
  }
}
