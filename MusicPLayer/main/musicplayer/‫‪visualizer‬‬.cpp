#include "musicplayerpage.h"
#include "ui_musicplayerpage.h"

void musicplayerpage::ChangeGraphicView(QPoint pos)
{

}

void musicplayerpage::processBuffer()
{
    QAudioBuffer buffer = decoder->read();
    QAudioFormat format = buffer.format();

    int fftSize = 1024;
    int sampleCount = buffer.sampleCount();

    // اطمینان از حداقل داده برای FFT
    if (sampleCount < fftSize) {
        // اگر داده کمتره، می‌تونید اینجا صبر کنید یا با صفر پر کنید
        return;
    }

    // آرایه‌های FFT
    fftw_complex *in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * fftSize);
    fftw_complex *out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * fftSize);

    // اگر کانال‌ها بیشتر از 1 هست، ما فقط کانال اول (چپ) رو می‌گیریم

    int channels = format.channelCount();

    const float* data = buffer.constData<float>();
    int samplesPerChannel = sampleCount / channels;

    if (format.sampleFormat() == QAudioFormat::Int16) {
        const qint16* data = buffer.constData<qint16>();

        for (int i = 0; i < fftSize; ++i) {
            double value = (i < samplesPerChannel) ? static_cast<double>(data[i]) : 0.0;
            in[i][0] = value;
            in[i][1] = 0.0;
        }
    } else if (format.sampleFormat() == QAudioFormat::Float) {
        const float* data = buffer.constData<float>();

        for (int i = 0; i < fftSize; ++i) {
            double value = (i < samplesPerChannel) ? static_cast<double>(data[i]) : 0.0;
            in[i][0] = value;
            in[i][1] = 0.0;
        }
    } else {
        qDebug() << "Unsupported audio format for FFT";
        fftw_free(in);
        fftw_free(out);
        return;
    }

    // انجام FFT
    fftw_plan plan = fftw_plan_dft_1d(fftSize, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);

    QVector<double> magnitudes;
    for (int i = 0; i < fftSize / 2; ++i) {
        double mag = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
        magnitudes.append(mag);
    }

    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);

    // رسم میله‌ها (visualizer)
    drawBars(magnitudes);
}


void musicplayerpage::drawBars(const QVector<double>& magnitudes)
{
    int numBars = 32;
    int binSize = magnitudes.size() / numBars;

    QVector<double> averagedBars;
    for (int i = 0; i < numBars; ++i) {
        double sum = 0;
        for (int j = 0; j < binSize; ++j) {
            sum += magnitudes[i * binSize + j];
        }
        averagedBars.append(sum / binSize);
    }

    scene->clear();

    int width = ui->graphicsView->width();
    int height = ui->graphicsView->height();
    int barWidth = width / numBars;

    for (int i = 0; i < numBars; ++i) {
        double barHeight = qMin(averagedBars[i] * 0.05, (double)height);
        scene->addRect(i * barWidth, height - barHeight, barWidth - 2, barHeight,
                       Qt::NoPen, QBrush(Qt::cyan));
    }
}
