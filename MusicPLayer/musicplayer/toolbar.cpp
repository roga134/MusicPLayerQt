#include "musicplayerpage.h"
#include "ui_musicplayerpage.h"

void musicplayerpage::on_actionprevios_song_triggered()
{
    this->on_pushButton_prev_clicked();
}

void musicplayerpage::on_actionplay_triggered()
{
    this->on_pushButton_play_clicked();
}

void musicplayerpage::on_actionnext_trak_triggered()
{
    this->on_pushButton_next_clicked();
}

void musicplayerpage::on_actionexit_2_triggered()
{
    qApp->quit();
    QCoreApplication::exit(0);
    this->close();
}

void musicplayerpage::on_actionDon_t_shuffel_triggered()
{
    shuffleMode = false;

    ui->pushButton_shufle->setIcon(QIcon(":/icons/image/shuffle-off.png"));
}

void musicplayerpage::on_actionshuffel_all_triggered()
{
    shuffleMode = true;

    ui->pushButton_shufle->setIcon(QIcon(":/icons/image/shuffle.png"));
}

void musicplayerpage::on_actionadd_playlist_triggered()
{
    on_pushButton_creatPlaylist_clicked();
}

void musicplayerpage::on_actionsave_playlist_triggered()
{
    on_pushButton_savePlaylist_clicked();
}

void musicplayerpage::on_actionload_playlist_triggered()
{
    on_pushButton_loadPlaylist_clicked();
}

void musicplayerpage::settoolbar()
{
    ui->actionUndo->setText("Undo\tCtrl+Z");
    ui->actionUndo->setShortcut(QKeySequence("Ctrl+Z"));

    ui->actionexit_2->setText("Quit\tCtrl+Q");
    ui->actionexit_2->setShortcut(QKeySequence("Ctrl+Q"));

    ui->actionnext_trak->setText("Next Track\tCtrl+N");
    ui->actionnext_trak->setShortcut(QKeySequence("Ctrl+N"));

    ui->actionprevios_song->setText("Previous Track\tCtrl+P");
    ui->actionprevios_song->setShortcut(QKeySequence("Ctrl+P"));

    ui->actionplay->setText("Play Track\tCtrl+S");
    ui->actionplay->setShortcut(QKeySequence("Ctrl+S"));

    ui->actionopen_file->setText("Open Files\tCtrl+O");
    ui->actionopen_file->setShortcut(QKeySequence("Ctrl+O"));

    ui->actionRemove_Track->setText("Remove Track\tCtrl+R");
    ui->actionRemove_Track->setShortcut(QKeySequence("Ctrl+R"));

    ui->actionDon_t_shuffel->setText("Don't Shuffle\tCtrl+Shift+S");
    ui->actionDon_t_shuffel->setShortcut(QKeySequence("Ctrl+Shift+S"));

    ui->actionshuffel_all->setText("Shuffle All\tCtrl+S");
    ui->actionDon_t_shuffel->setShortcut(QKeySequence("Ctrl+S"));

    ui->actionDon_t_repeat->setText("Don't Repeat Playlist\tCtrl+Shift+M");
    ui->actionDon_t_repeat->setShortcut(QKeySequence("Ctrl+Shift+M"));

    ui->actionrepeat_trak->setText("Repeat Track\tCtrl+M, then 1");
    ui->actionrepeat_trak->setShortcut(QKeySequence());

    ui->actionrepeat_playlist->setText("Repeat Playlist\tCtrl+M");
    ui->actionrepeat_playlist->setShortcut(QKeySequence("Ctrl+M"));

    ui->actionadd_playlist->setText("Add Playlist\tCtrl+A");
    ui->actionadd_playlist->setShortcut(QKeySequence("Ctrl+A"));

    ui->actionsave_playlist->setText("Save Playlist\tCtrl+Shift+S");
    ui->actionsave_playlist->setShortcut(QKeySequence("Ctrl+Shift+S"));

    ui->actionload_playlist->setText("Load Playlist\tCtrl+L");
    ui->actionload_playlist->setShortcut(QKeySequence("Ctrl+L"));
}

void musicplayerpage::keyPressEvent(QKeyEvent *event)
{
    static bool ctrlMPressed = false;

    if (event->modifiers() & Qt::ControlModifier && event->key() == Qt::Key_M) {
        ctrlMPressed = true;
        return;
    }

    if (ctrlMPressed && event->key() == Qt::Key_1) {
        ctrlMPressed = false;
        ui->actionDon_t_repeat->trigger();
        return;
    }

    ctrlMPressed = false;
    QMainWindow::keyPressEvent(event);
}

void musicplayerpage::on_actionDon_t_repeat_triggered()
{
    ui->pushButton_mode3->setIcon(QIcon(":/icons/image/no-repeat.png"));
    execute_Command(std::make_unique<SetRepeatModeCommand>(repeatMode, NoRepeat));
}

void musicplayerpage::on_actionrepeat_trak_triggered()
{
    ui->pushButton_mode3->setIcon(QIcon(":/icons/image/repeat-one.png"));
    execute_Command(std::make_unique<SetRepeatModeCommand>(repeatMode,RepreatOne));
}

void musicplayerpage::on_actionrepeat_playlist_triggered()
{
    ui->pushButton_mode3->setIcon(QIcon(":/icons/image/repeat.png"));
    execute_Command(std::make_unique<SetRepeatModeCommand>(repeatMode, RepeatAll));
}
