#include "car_selector.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "selfdrive/common/params.h"

CarSelectorWindow::CarSelectorWindow(QWidget *parent) : QDialog(parent) {
  QVBoxLayout *layout = new QVBoxLayout(this);

  QLabel *label = new QLabel("请选择车型：");
  layout->addWidget(label);

  QListWidget *carList = new QListWidget();
  layout->addWidget(carList);

  // 加载支持的车型列表
  QFile file("../selfdrive/data/supported_cars.json");
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject carData = doc.object();

    // 遍历品牌和车型
    for (auto brand : carData.keys()) {
      QJsonArray models = carData.value(brand).toArray();
      for (const auto &model : models) {
        carList->addItem(brand + " " + model.toString());
      }
    }
  } else {
    carList->addItem("无法加载车型列表");
  }

  QPushButton *confirmButton = new QPushButton("确认");
  layout->addWidget(confirmButton);

  // 保存用户选择
  QObject::connect(confirmButton, &QPushButton::clicked, [=]() {
    if (carList->currentItem()) {
      QString selectedCar = carList->currentItem()->text();
      Params().put("ForceCarModel", selectedCar.toStdString());
    }
    close();
  });
}
