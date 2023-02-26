#include "window.hpp"

Window::Window(int w, int h, QString t) : m_width(w), m_height(h), m_title(t)
{
	resize(m_width, m_height);
	setWindowTitle(m_title);

	createActions();
	addMenus();
	addToolBars();
	createStatusBar();

	m_tabs = new QTabWidget;

	m_tabs->addTab(createWebPageTab(tr("https://google.com")), tr("New Page"));

	connect(m_tabs, SIGNAL(currentChange(int)), this, SLOT(changingTab(int)));

	setCentralWidget(m_tabs);
}


/*
 *
 *   Init methods : to create actions, menus, toolbar and statusBar
 *
 */

void Window::createActions()
{
	m_actionNewTab = new QAction(tr("New Tab"), this);
	m_actionNewTab->setShortcut(QKeySequence(tr("Ctrl+T")));
	m_actionNewTab->setIcon(QIcon("icons/add-new.png"));

	m_actionCloseTab = new QAction("Close Tab", this);
	//m_actionCloseTab->
	
	m_actionQuit = new QAction(tr("Quit"), this);
	m_actionQuit->setShortcut(QKeySequence("Ctrl+Q"));

	m_actionAbout = new QAction(tr("About Us"), this);
	
	m_actionAboutQt = new QAction(tr("About Qt"), this);

	m_actionBack = new QAction(tr("Back"), this);
	m_actionBack->setIcon(QIcon("icons/left.png"));

	m_actionNext = new QAction(tr("Next"), this);
	m_actionNext->setIcon(QIcon("icons/right.png"));

	m_actionStop = new QAction(tr("Stop"), this);
	m_actionStop->setIcon(QIcon("icons/stop.png"));

	m_actionRefresh = new QAction(tr("Refresh"), this);
	m_actionRefresh->setIcon(QIcon("icons/refresh.png"));

	m_actionHome = new QAction(tr("Home"), this);
	m_actionHome->setIcon(QIcon("icons/home.png"));

	m_actionGo = new QAction(tr("Go"), this);
	m_actionGo->setIcon(QIcon("icons/go.png"));
	
}

void Window::addMenus()
{
	QMenu *menuFile = menuBar()->addMenu(tr("&File"));

		menuFile->addAction(m_actionQuit);

	QMenu *menuBrowsing = menuBar()->addMenu(tr("&Browsing"));
		
		menuBrowsing->addAction(m_actionNewTab);
		menuBrowsing->addAction(m_actionCloseTab);
		menuBrowsing->addAction(m_actionBack);
		menuBrowsing->addAction(m_actionNext);
		menuBrowsing->addAction(m_actionStop);
		menuBrowsing->addAction(m_actionRefresh);
		menuBrowsing->addAction(m_actionHome);

	QMenu *menuHelp = menuBar()->addMenu(tr("?"));
		
		menuHelp->addAction(m_actionAbout);
		menuHelp->addAction(m_actionAboutQt);
		
}

void Window::addToolBars()
{
	QToolBar *toolBar = addToolBar(tr("Browsers ToolBar"));

	toolBar->addAction(m_actionBack);
	toolBar->addAction(m_actionNext);
	toolBar->addAction(m_actionStop);
	toolBar->addAction(m_actionRefresh);
	toolBar->addAction(m_actionHome);
	
	m_lineEditUrl = new QLineEdit("", this);
	toolBar->addWidget(m_lineEditUrl);

	toolBar->addAction(m_actionGo);
}

void Window::createStatusBar()
{
	m_statusProgress = new QProgressBar();
}


QWidget* Window::createWebPageTab(QString url)
{
	QWidget *tabPage = new QWidget;
	QWebView *webPage = new QWebView;

	QVBoxLayout *layout = new QVBoxLayout;

	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(webPage);
	tabPage->setLayout(layout);

	if (url.isEmpty())
	{
		webPage->load(QUrl("html/blank_page.html"));
	}
	else
	{
		if (url.left(7) != "http://" && url.left(8) != "https://")
		{
			url = "https://" + url;
		}

		webPage->load(QUrl(url));
	}

	
	connect(webPage, SIGNAL(titleChanged(QString)), this, SLOT(changeTitle(QString)));
	connect(webPage, SIGNAL(urlChanged(QUrl)), this, SLOT(changeUrl(QUrl)));
	connect(wepPage, SIGNAL(loadStarted()), this, SLOT(loadingStart()));
	connect(webPage, SIGNAL(loadProgress(int)), this, SLOT(loadingProgress(int)));
	connect(webPage, SIGNAL(loadFinished(int)), this, SLOT(loadingFinished(bool)));

	return tabPage;	
}

QWebView *Window::actualPage()
{
	return m_tabs->currentWidget()->findChild<QWebView* >();
}


/**
 *
 *   SLOTS
 *
 *
 **/

void Window::back()
{
	actualPage()->back();
}

void Window::next()
{
	actualPage->forward();
}

void Window::stop()
{
	actualPage()->stop();
}

void Window::refresh()
{
	actualPage()->reload();
}

void Window::home()
{
	actualPage()->load(QUrl(tr("index.html")));
}

void Window::about()
{
	QMessageBox::information(this, tr("Kmk Browser is a browser"))
}

void Window::about()
{
}

void Window::newTab()
{
	int indexNewTab = m_tabs->addTab(createWebPageTab(), tr("(New Page)"));
	m_tabs->setCurrentIndex(indexNewTab);
	m_lineEditUrl->setText("");
	m_lineEditUrl->setFocus(Qt::OtherFocusReason);
}

void Window::closeTab()
{
	if (m_tabs->count() > 1)
	{
		m_tabs->removeTab(m_tabs->currentIndex());
	}
	else
	{
		QMessageBox::critical(this, tr("This is could close your browser"));
	}
}

void Window::loadPage()
{
	QString url = m_lineEditUrl->text();

	if (url.left(7) != "http://" && url.left(8) != "https://")
	{
		url = "https://" + url;
		m_lineEditurl->setText(url);
	}
	
	actualPage()->load(QUrl(url));
}

void Window::changeTab(int index)
{
	changeTitle(actualPage()->title());
	changeUrl(actualPage()->url());
}

void Window::changeTitle(const QString & title)
{
	QString shortTitle = title;

	if (title.size() > 40)
	{
		shortTitle = title.left(40) + "...";
	}

	setWindowTitle(shortTitle + " - " + tr("KMK Browser"));
	m_tabs->setTabText(m_tabs->currentIndex(), shortTitle);
}

void Window::changeUrl(const QString & url)
{
	if (url.toString() != tr("html/index.html"))
	{
		m_lineEditUrl->setText(url.toString());
	}

}

void Window::loadingStart()
{
	m_statusProgress->setVisible(true);
}

void Window::loadingProgress(int value)
{
	m_statusProgress->setValue(value);
}

void Window::loadingFinished(bool ok)
{
	m_statusProgress->setVisible(false);
	statusBar()->showMessage(tr("Ready"), 2000);
