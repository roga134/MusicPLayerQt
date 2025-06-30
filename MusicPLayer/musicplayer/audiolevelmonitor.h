#ifndef AUDIOLEVELMONITOR_H
#define AUDIOLEVELMONITOR_H

#include <QAudioInput>
#include <QIODevice>
#include <QVector>

class AudioLevelMonitor : public QObject {
    Q_OBJECT
public:
    AudioLevelMonitor(VisualizerWidget* visualizer, QObject* parent = nullptr)
        : QObject(parent), m_visualizer(visualizer)
    {
        QAudioFormat format;
        format.setSampleRate(44100);
        format.setChannelCount(1);
        format.setSampleSize(16);
        format.setCodec("audio/pcm");
        format.setByteOrder(QAudioFormat::LittleEndian);
        format.setSampleType(QAudioFormat::SignedInt);

        QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
        if (!info.isFormatSupported(format)) {
            qWarning() << "Default format not supported, trying to use nearest";
            format = info.nearestFormat(format);
        }

        m_audioInput = new QAudioInput(format, this);
        m_ioDevice = m_audioInput->start();
        connect(m_ioDevice, &QIODevice::readyRead, this, &AudioLevelMonitor::processAudioData);
    }

private slots:
    void processAudioData() {
        QByteArray data = m_ioDevice->readAll();

        // داده‌های صوتی 16 بیتی signed هستند
        const int16_t* samples = reinterpret_cast<const int16_t*>(data.constData());
        int sampleCount = data.size() / 2;

        float level = 0;
        for (int i = 0; i < sampleCount; ++i) {
            level += std::abs(samples[i]);
        }
        if (sampleCount > 0)
            level /= sampleCount;

        // نرمال‌سازی سطح صدا به [0, 1]
        float normalizedLevel = qMin(level / 32768.0f, 1.0f);

        QVector<float> levels(20, normalizedLevel); // فرضاً 20 بار با یک سطح مشابه
        m_visualizer->setLevels(levels);
    }

private:
    VisualizerWidget* m_visualizer;
    QAudioInput* m_audioInput = nullptr;
    QIODevice* m_ioDevice = nullptr;
};

#endif // AUDIOLEVELMONITOR_H
