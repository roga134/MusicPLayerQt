/********************************************************************************
** Form generated from reading UI file 'musicplayerpage.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSICPLAYERPAGE_H
#define UI_MUSICPLAYERPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_musicplayerpage
{
public:
    QAction *actionopen_file;
    QAction *actionprevios_song;
    QAction *actionplay;
    QAction *actionnext_trak;
    QAction *actionexit;
    QAction *actionAdd_Track;
    QAction *actionRemove_Track;
    QAction *actionDon_t_shuffel;
    QAction *actionshuffel_all;
    QAction *actionDon_t_repeat;
    QAction *actionrepeat_trak;
    QAction *actionadd_playlist;
    QAction *actionsave_playlist;
    QAction *actionload_playlist;
    QAction *actionUndo;
    QAction *actionexit_2;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_files;
    QPushButton *pushButton_devices;
    QPushButton *pushButton_server;
    QPushButton *pushButton_client;
    QPushButton *pushButton_chat;
    QPushButton *pushButton_info;
    QLabel *ignore_label;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_back;
    QPushButton *pushButton_home;
    QPushButton *pushButton_forward;
    QLabel *label;
    QListView *generalListView;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_creatPlaylist;
    QPushButton *pushButton_savePlaylist;
    QPushButton *pushButton_loadPlaylist;
    QLineEdit *lineEdit;
    QTabWidget *tabWidget;
    QGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_played;
    QSlider *time;
    QLabel *label_remaning;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_mute;
    QSlider *volum;
    QLabel *volumlabel;
    QPushButton *pushButton_shufle;
    QPushButton *pushButton_prev;
    QPushButton *pushButton_play;
    QPushButton *pushButton_next;
    QPushButton *pushButton_mode3;
    QLabel *currentSongLabel;
    QMenuBar *menubar;
    QMenu *menuMusic;
    QMenu *menuPlaylist;
    QMenu *menuShuffel_mode;
    QMenu *menuRepeat_mode;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *musicplayerpage)
    {
        if (musicplayerpage->objectName().isEmpty())
            musicplayerpage->setObjectName("musicplayerpage");
        musicplayerpage->resize(1002, 600);
        actionopen_file = new QAction(musicplayerpage);
        actionopen_file->setObjectName("actionopen_file");
        actionprevios_song = new QAction(musicplayerpage);
        actionprevios_song->setObjectName("actionprevios_song");
        actionplay = new QAction(musicplayerpage);
        actionplay->setObjectName("actionplay");
        actionnext_trak = new QAction(musicplayerpage);
        actionnext_trak->setObjectName("actionnext_trak");
        actionexit = new QAction(musicplayerpage);
        actionexit->setObjectName("actionexit");
        actionAdd_Track = new QAction(musicplayerpage);
        actionAdd_Track->setObjectName("actionAdd_Track");
        actionRemove_Track = new QAction(musicplayerpage);
        actionRemove_Track->setObjectName("actionRemove_Track");
        actionDon_t_shuffel = new QAction(musicplayerpage);
        actionDon_t_shuffel->setObjectName("actionDon_t_shuffel");
        actionshuffel_all = new QAction(musicplayerpage);
        actionshuffel_all->setObjectName("actionshuffel_all");
        actionDon_t_repeat = new QAction(musicplayerpage);
        actionDon_t_repeat->setObjectName("actionDon_t_repeat");
        actionrepeat_trak = new QAction(musicplayerpage);
        actionrepeat_trak->setObjectName("actionrepeat_trak");
        actionadd_playlist = new QAction(musicplayerpage);
        actionadd_playlist->setObjectName("actionadd_playlist");
        actionsave_playlist = new QAction(musicplayerpage);
        actionsave_playlist->setObjectName("actionsave_playlist");
        actionload_playlist = new QAction(musicplayerpage);
        actionload_playlist->setObjectName("actionload_playlist");
        actionUndo = new QAction(musicplayerpage);
        actionUndo->setObjectName("actionUndo");
        actionexit_2 = new QAction(musicplayerpage);
        actionexit_2->setObjectName("actionexit_2");
        centralwidget = new QWidget(musicplayerpage);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");

        verticalLayout_3->addLayout(verticalLayout_2);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        pushButton_files = new QPushButton(centralwidget);
        pushButton_files->setObjectName("pushButton_files");
        pushButton_files->setFlat(true);

        verticalLayout->addWidget(pushButton_files);

        pushButton_devices = new QPushButton(centralwidget);
        pushButton_devices->setObjectName("pushButton_devices");
        pushButton_devices->setFlat(true);

        verticalLayout->addWidget(pushButton_devices);

        pushButton_server = new QPushButton(centralwidget);
        pushButton_server->setObjectName("pushButton_server");
        pushButton_server->setFlat(true);

        verticalLayout->addWidget(pushButton_server);

        pushButton_client = new QPushButton(centralwidget);
        pushButton_client->setObjectName("pushButton_client");
        pushButton_client->setFlat(true);

        verticalLayout->addWidget(pushButton_client);

        pushButton_chat = new QPushButton(centralwidget);
        pushButton_chat->setObjectName("pushButton_chat");
        pushButton_chat->setFlat(true);

        verticalLayout->addWidget(pushButton_chat);

        pushButton_info = new QPushButton(centralwidget);
        pushButton_info->setObjectName("pushButton_info");
        pushButton_info->setFlat(true);

        verticalLayout->addWidget(pushButton_info);

        ignore_label = new QLabel(centralwidget);
        ignore_label->setObjectName("ignore_label");

        verticalLayout->addWidget(ignore_label);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton_back = new QPushButton(centralwidget);
        pushButton_back->setObjectName("pushButton_back");
        pushButton_back->setFlat(true);

        horizontalLayout_2->addWidget(pushButton_back);

        pushButton_home = new QPushButton(centralwidget);
        pushButton_home->setObjectName("pushButton_home");
        pushButton_home->setFlat(true);

        horizontalLayout_2->addWidget(pushButton_home);

        pushButton_forward = new QPushButton(centralwidget);
        pushButton_forward->setObjectName("pushButton_forward");
        pushButton_forward->setFlat(true);

        horizontalLayout_2->addWidget(pushButton_forward);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label);


        verticalLayout_5->addLayout(horizontalLayout_2);

        generalListView = new QListView(centralwidget);
        generalListView->setObjectName("generalListView");

        verticalLayout_5->addWidget(generalListView);


        horizontalLayout->addLayout(verticalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_creatPlaylist = new QPushButton(centralwidget);
        pushButton_creatPlaylist->setObjectName("pushButton_creatPlaylist");
        pushButton_creatPlaylist->setMaximumSize(QSize(20, 16777215));
        pushButton_creatPlaylist->setFlat(true);

        horizontalLayout_3->addWidget(pushButton_creatPlaylist);

        pushButton_savePlaylist = new QPushButton(centralwidget);
        pushButton_savePlaylist->setObjectName("pushButton_savePlaylist");
        pushButton_savePlaylist->setMaximumSize(QSize(20, 16777215));
        pushButton_savePlaylist->setFlat(true);

        horizontalLayout_3->addWidget(pushButton_savePlaylist);

        pushButton_loadPlaylist = new QPushButton(centralwidget);
        pushButton_loadPlaylist->setObjectName("pushButton_loadPlaylist");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_loadPlaylist->sizePolicy().hasHeightForWidth());
        pushButton_loadPlaylist->setSizePolicy(sizePolicy1);
        pushButton_loadPlaylist->setMaximumSize(QSize(20, 16777215));
        pushButton_loadPlaylist->setFlat(true);

        horizontalLayout_3->addWidget(pushButton_loadPlaylist);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_3->addWidget(lineEdit);


        verticalLayout_6->addLayout(horizontalLayout_3);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");

        verticalLayout_6->addWidget(tabWidget);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");

        verticalLayout_6->addWidget(graphicsView);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_played = new QLabel(centralwidget);
        label_played->setObjectName("label_played");

        horizontalLayout_5->addWidget(label_played);

        time = new QSlider(centralwidget);
        time->setObjectName("time");
        time->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(time);

        label_remaning = new QLabel(centralwidget);
        label_remaning->setObjectName("label_remaning");

        horizontalLayout_5->addWidget(label_remaning);


        verticalLayout_6->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        pushButton_mute = new QPushButton(centralwidget);
        pushButton_mute->setObjectName("pushButton_mute");
        pushButton_mute->setFlat(true);

        horizontalLayout_4->addWidget(pushButton_mute);

        volum = new QSlider(centralwidget);
        volum->setObjectName("volum");
        volum->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(volum);

        volumlabel = new QLabel(centralwidget);
        volumlabel->setObjectName("volumlabel");

        horizontalLayout_4->addWidget(volumlabel);

        pushButton_shufle = new QPushButton(centralwidget);
        pushButton_shufle->setObjectName("pushButton_shufle");
        pushButton_shufle->setFlat(true);

        horizontalLayout_4->addWidget(pushButton_shufle);

        pushButton_prev = new QPushButton(centralwidget);
        pushButton_prev->setObjectName("pushButton_prev");
        pushButton_prev->setFlat(true);

        horizontalLayout_4->addWidget(pushButton_prev);

        pushButton_play = new QPushButton(centralwidget);
        pushButton_play->setObjectName("pushButton_play");
        pushButton_play->setFlat(true);

        horizontalLayout_4->addWidget(pushButton_play);

        pushButton_next = new QPushButton(centralwidget);
        pushButton_next->setObjectName("pushButton_next");
        pushButton_next->setFlat(true);

        horizontalLayout_4->addWidget(pushButton_next);

        pushButton_mode3 = new QPushButton(centralwidget);
        pushButton_mode3->setObjectName("pushButton_mode3");
        pushButton_mode3->setFlat(true);

        horizontalLayout_4->addWidget(pushButton_mode3);


        verticalLayout_6->addLayout(horizontalLayout_4);


        verticalLayout_4->addLayout(verticalLayout_6);

        currentSongLabel = new QLabel(centralwidget);
        currentSongLabel->setObjectName("currentSongLabel");

        verticalLayout_4->addWidget(currentSongLabel);


        horizontalLayout->addLayout(verticalLayout_4);

        musicplayerpage->setCentralWidget(centralwidget);
        menubar = new QMenuBar(musicplayerpage);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1002, 23));
        menuMusic = new QMenu(menubar);
        menuMusic->setObjectName("menuMusic");
        menuPlaylist = new QMenu(menubar);
        menuPlaylist->setObjectName("menuPlaylist");
        menuShuffel_mode = new QMenu(menuPlaylist);
        menuShuffel_mode->setObjectName("menuShuffel_mode");
        menuRepeat_mode = new QMenu(menuPlaylist);
        menuRepeat_mode->setObjectName("menuRepeat_mode");
        musicplayerpage->setMenuBar(menubar);
        statusbar = new QStatusBar(musicplayerpage);
        statusbar->setObjectName("statusbar");
        musicplayerpage->setStatusBar(statusbar);

        menubar->addAction(menuMusic->menuAction());
        menubar->addAction(menuPlaylist->menuAction());
        menuMusic->addAction(actionopen_file);
        menuMusic->addSeparator();
        menuMusic->addAction(actionprevios_song);
        menuMusic->addAction(actionplay);
        menuMusic->addAction(actionnext_trak);
        menuMusic->addSeparator();
        menuMusic->addAction(actionUndo);
        menuMusic->addSeparator();
        menuMusic->addAction(actionexit_2);
        menuPlaylist->addAction(actionRemove_Track);
        menuPlaylist->addSeparator();
        menuPlaylist->addAction(menuShuffel_mode->menuAction());
        menuPlaylist->addAction(menuRepeat_mode->menuAction());
        menuPlaylist->addSeparator();
        menuPlaylist->addAction(actionadd_playlist);
        menuPlaylist->addAction(actionsave_playlist);
        menuPlaylist->addAction(actionload_playlist);
        menuPlaylist->addSeparator();
        menuShuffel_mode->addAction(actionDon_t_shuffel);
        menuShuffel_mode->addAction(actionshuffel_all);
        menuRepeat_mode->addAction(actionDon_t_repeat);
        menuRepeat_mode->addAction(actionrepeat_trak);

        retranslateUi(musicplayerpage);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(musicplayerpage);
    } // setupUi

    void retranslateUi(QMainWindow *musicplayerpage)
    {
        musicplayerpage->setWindowTitle(QCoreApplication::translate("musicplayerpage", "musicplayerpage", nullptr));
        actionopen_file->setText(QCoreApplication::translate("musicplayerpage", "open file", nullptr));
        actionprevios_song->setText(QCoreApplication::translate("musicplayerpage", "previous trak", nullptr));
        actionplay->setText(QCoreApplication::translate("musicplayerpage", "play", nullptr));
        actionnext_trak->setText(QCoreApplication::translate("musicplayerpage", "next trak", nullptr));
        actionexit->setText(QCoreApplication::translate("musicplayerpage", "exit", nullptr));
        actionAdd_Track->setText(QCoreApplication::translate("musicplayerpage", "Add Track", nullptr));
        actionRemove_Track->setText(QCoreApplication::translate("musicplayerpage", "Remove Track", nullptr));
        actionDon_t_shuffel->setText(QCoreApplication::translate("musicplayerpage", "Don't shuffel", nullptr));
        actionshuffel_all->setText(QCoreApplication::translate("musicplayerpage", "shuffel all", nullptr));
        actionDon_t_repeat->setText(QCoreApplication::translate("musicplayerpage", "Don't repeat", nullptr));
        actionrepeat_trak->setText(QCoreApplication::translate("musicplayerpage", "repeat track", nullptr));
        actionadd_playlist->setText(QCoreApplication::translate("musicplayerpage", "add playlist", nullptr));
        actionsave_playlist->setText(QCoreApplication::translate("musicplayerpage", "save playlist", nullptr));
        actionload_playlist->setText(QCoreApplication::translate("musicplayerpage", "load playlist", nullptr));
        actionUndo->setText(QCoreApplication::translate("musicplayerpage", "Undo", nullptr));
        actionexit_2->setText(QCoreApplication::translate("musicplayerpage", "exit", nullptr));
        pushButton_files->setText(QCoreApplication::translate("musicplayerpage", "Files", nullptr));
        pushButton_devices->setText(QCoreApplication::translate("musicplayerpage", "Devices", nullptr));
        pushButton_server->setText(QCoreApplication::translate("musicplayerpage", "Server", nullptr));
        pushButton_client->setText(QCoreApplication::translate("musicplayerpage", "Client", nullptr));
        pushButton_chat->setText(QCoreApplication::translate("musicplayerpage", "Chat", nullptr));
        pushButton_info->setText(QCoreApplication::translate("musicplayerpage", "information", nullptr));
        ignore_label->setText(QString());
        pushButton_back->setText(QString());
        pushButton_home->setText(QString());
        pushButton_forward->setText(QString());
        label->setText(QString());
        pushButton_creatPlaylist->setText(QString());
        pushButton_savePlaylist->setText(QString());
        pushButton_loadPlaylist->setText(QString());
        label_played->setText(QString());
        label_remaning->setText(QString());
        pushButton_mute->setText(QString());
        volumlabel->setText(QString());
        pushButton_shufle->setText(QString());
        pushButton_prev->setText(QString());
        pushButton_play->setText(QString());
        pushButton_next->setText(QString());
        pushButton_mode3->setText(QString());
        currentSongLabel->setText(QString());
        menuMusic->setTitle(QCoreApplication::translate("musicplayerpage", "Music", nullptr));
        menuPlaylist->setTitle(QCoreApplication::translate("musicplayerpage", "Playlist", nullptr));
        menuShuffel_mode->setTitle(QCoreApplication::translate("musicplayerpage", "Shuffel mode", nullptr));
        menuRepeat_mode->setTitle(QCoreApplication::translate("musicplayerpage", "Repeat mode", nullptr));
    } // retranslateUi

};

namespace Ui {
    class musicplayerpage: public Ui_musicplayerpage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSICPLAYERPAGE_H
