#ifndef HEADER_WINDOW_HPP
#define HEADER_WINDOW_HPP

#include <QtWidgets>
#include <QtWebKitWidgets>

class Window : public QMainWindow
{
	Q_OBJECT
	
	public:
		Window(int, int, QString);

	private:
		void createActions();
		void addMenus();
		void addToolBars();
		void createStatusBar();

		QWidget* createWebPageTab(QString);

	private slots:
		void loadPage();
		void changTab(int);

		void changeTitle(const QString&);
		void changeUrl(const QString&);
		void loadingStart();
		void loadingProgress(int);
		void loadingFinished(bool);

		void back();
		void next();
		void home();
		void stop();
		void refresh();

		void about();
		void aboutQt();

		void newTab();
		void closeTab();



	private:
		int m_width;
		int m_height;
		QString m_title;

		QTabWidget *m_tabs;

		QAction *m_actionNewTab;
		QAction *m_actionCloseTab;
		QAction *m_actionQuit;
		QAction *m_actionAbout;
		QAction *m_actionAboutQt;
		QAction *m_actionBack;
		QAction *m_actionNext;
		QAction *m_actionStop;
		QAction *m_actionRefresh;
		QAction *m_actionHome;
		QAction *m_actionGo;

		QLineEdit *m_lineEditUrl;
		QProgressBar *m_statusProgress;
};


#endif //HEADER_WINDOW_HPP
