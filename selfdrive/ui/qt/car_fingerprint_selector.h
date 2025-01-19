#pragma once

#include <QWidget>
#include <QListWidget>

class CarFingerprintSelector : public QWidget {
  Q_OBJECT

public:
  explicit CarFingerprintSelector(QWidget *parent = nullptr);

private:
  QListWidget *fingerprint_list;
  void loadFingerprints();
};
