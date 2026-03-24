/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Assistant of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "helpviewer.h"
#include "helpviewer_p.h"

//#include "centralwidget.h"
//#include "helpenginewrapper.h"
//#include "openpagesmanager.h"
//#include "tracer.h"
#include "helpenginesingleton.h"
#include <QHelpEngine>

#include <QtCore/QFileInfo>
#include <QtCore/QString>
#include <QtCore/QTimer>

#include <QtGui/QApplication>
#include <QtGui/QWheelEvent>

#include <QtHelp/QHelpEngineCore>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

QT_BEGIN_NAMESPACE

// -- HelpNetworkReply

class HelpNetworkReply : public QNetworkReply
{
public:
    HelpNetworkReply(const QNetworkRequest &request, const QByteArray &fileData,
        const QString &mimeType);

    virtual void abort();

    virtual qint64 bytesAvailable() const
        { return data.length() + QNetworkReply::bytesAvailable(); }

protected:
    virtual qint64 readData(char *data, qint64 maxlen);

private:
    QByteArray data;
    qint64 origLen;
};

HelpNetworkReply::HelpNetworkReply(const QNetworkRequest &request,
        const QByteArray &fileData, const QString& mimeType)
    : data(fileData), origLen(fileData.length())
{
    
    setRequest(request);
    setOpenMode(QIODevice::ReadOnly);

    setHeader(QNetworkRequest::ContentTypeHeader, mimeType);
    setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(origLen));
    QTimer::singleShot(0, this, SIGNAL(metaDataChanged()));
    QTimer::singleShot(0, this, SIGNAL(readyRead()));
    QTimer::singleShot(0, this, SIGNAL(finished()));
}

void HelpNetworkReply::abort()
{
    
}

qint64 HelpNetworkReply::readData(char *buffer, qint64 maxlen)
{
    
    qint64 len = qMin(qint64(data.length()), maxlen);
    if (len) {
        memcpy(buffer, data.constData(), len);
        data.remove(0, len);
    }
    if (!data.length())
        QTimer::singleShot(0, this, SIGNAL(finished()));
    return len;
}

// -- HelpNetworkAccessManager

class HelpNetworkAccessManager : public QNetworkAccessManager
{
public:
    HelpNetworkAccessManager(QObject *parent);

protected:
    virtual QNetworkReply *createRequest(Operation op,
        const QNetworkRequest &request, QIODevice *outgoingData = 0);
};

HelpNetworkAccessManager::HelpNetworkAccessManager(QObject *parent)
    : QNetworkAccessManager(parent)
{
    
}

QNetworkReply *HelpNetworkAccessManager::createRequest(Operation /*op*/,
    const QNetworkRequest &request, QIODevice* /*outgoingData*/)
{
    
    QString url = request.url().toString();

	const QHelpEngine& engine=*HelpEngineSingleton::instance();
    //const HelpEngineWrapper &engine = HelpEngineWrapper::instance();

    bool fileFound = engine.findFile(url).isValid();
    //if (!fileFound && HelpViewer::isLocalUrl(request.url()))
        //url = HelpViewer::fixupVirtualFolderForUrl(&engine, request.url(), &fileFound);

    const QString &mimeType = HelpViewer::mimeFromUrl(url);
    const QByteArray &data = fileFound ? engine.fileData(url)
        : HelpViewer::PageNotFoundMessage.arg(url).toUtf8();

    return new HelpNetworkReply(request, data, mimeType.isEmpty()
        ? QLatin1String("application/octet-stream") : mimeType);
}

// -- HelpPage

class HelpPage : public QWebPage
{
public:
    HelpPage(QObject *parent);

protected:
    virtual QWebPage *createWindow(QWebPage::WebWindowType);
    virtual void triggerAction(WebAction action, bool checked = false);

    virtual bool acceptNavigationRequest(QWebFrame *frame,
        const QNetworkRequest &request, NavigationType type);

private:
    bool closeNewTabIfNeeded;

    friend class HelpViewer;
    QUrl m_loadingUrl;
    Qt::MouseButtons m_pressedButtons;
    Qt::KeyboardModifiers m_keyboardModifiers;
};

HelpPage::HelpPage(QObject *parent)
    : QWebPage(parent)
    , closeNewTabIfNeeded(false)
    , m_pressedButtons(Qt::NoButton)
    , m_keyboardModifiers(Qt::NoModifier)
{
    
}

QWebPage *HelpPage::createWindow(QWebPage::WebWindowType)
{
    
	/*
    HelpPage* newPage = static_cast<HelpPage*>(OpenPagesManager::instance()
        ->createPage()->page());
    newPage->closeNewTabIfNeeded = closeNewTabIfNeeded;
    closeNewTabIfNeeded = false;
    return newPage;
	*/
	return NULL;
}

void HelpPage::triggerAction(WebAction action, bool checked)
{
    
    switch (action) {
        case OpenLinkInNewWindow:
            closeNewTabIfNeeded = true;
        default:        // fall through
            QWebPage::triggerAction(action, checked);
            break;
    }
}

bool HelpPage::acceptNavigationRequest(QWebFrame *,
    const QNetworkRequest &request, QWebPage::NavigationType type)
{
    
	/*
    const bool closeNewTab = closeNewTabIfNeeded;
    closeNewTabIfNeeded = false;

    const QUrl &url = request.url();
    if (HelpViewer::launchWithExternalApp(url)) {
        if (closeNewTab)
            QMetaObject::invokeMethod(OpenPagesManager::instance(), "closeCurrentPage");
        return false;
    }

    if (type == QWebPage::NavigationTypeLinkClicked
        && (m_keyboardModifiers & Qt::ControlModifier || m_pressedButtons == Qt::MidButton)) {
            m_pressedButtons = Qt::NoButton;
            m_keyboardModifiers = Qt::NoModifier;
            OpenPagesManager::instance()->createPage(url);
            return false;
    }

    m_loadingUrl = url; // because of async page loading, we will hit some kind
    // of race condition while using a remote command, like a combination of
    // SetSource; SyncContent. SetSource would be called and SyncContents shortly
    // afterwards, but the page might not have finished loading and the old url
    // would be returned.
	*/

    return true;
}

// -- HelpViewer

HelpViewer::HelpViewer(qreal zoom, QWidget *parent)
    : QWebView(parent)
    , d(new HelpViewerPrivate)
{
    
    setAcceptDrops(false);
    settings()->setAttribute(QWebSettings::JavaEnabled, false);
    settings()->setAttribute(QWebSettings::PluginsEnabled, false);

    setPage(new HelpPage(this));
    page()->setNetworkAccessManager(new HelpNetworkAccessManager(this));

    QAction* action = pageAction(QWebPage::OpenLinkInNewWindow);
    action->setText(tr("Open Link in New Page"));

    pageAction(QWebPage::DownloadLinkToDisk)->setVisible(false);
    pageAction(QWebPage::DownloadImageToDisk)->setVisible(false);
    pageAction(QWebPage::OpenImageInNewWindow)->setVisible(false);

    connect(pageAction(QWebPage::Copy), SIGNAL(changed()), this,
        SLOT(actionChanged()));
    connect(pageAction(QWebPage::Back), SIGNAL(changed()), this,
        SLOT(actionChanged()));
    connect(pageAction(QWebPage::Forward), SIGNAL(changed()), this,
        SLOT(actionChanged()));
    connect(page(), SIGNAL(linkHovered(QString, QString, QString)), this,
        SIGNAL(highlighted(QString)));
    connect(this, SIGNAL(urlChanged(QUrl)), this, SIGNAL(sourceChanged(QUrl)));
    connect(this, SIGNAL(loadStarted()), this, SLOT(setLoadStarted()));
    connect(this, SIGNAL(loadFinished(bool)), this, SLOT(setLoadFinished(bool)));
    connect(this, SIGNAL(titleChanged(QString)), this, SIGNAL(titleChanged()));
    connect(page(), SIGNAL(printRequested(QWebFrame*)), this, SIGNAL(printRequested()));

    setFont(viewerFont());
    setTextSizeMultiplier(zoom == 0.0 ? 1.0 : zoom);
}

QFont HelpViewer::viewerFont() const
{
    
	/*
    if (HelpEngineWrapper::instance().usesBrowserFont())
        return HelpEngineWrapper::instance().browserFont();

    QWebSettings *webSettings = QWebSettings::globalSettings();
    return QFont(webSettings->fontFamily(QWebSettings::StandardFont),
        webSettings->fontSize(QWebSettings::DefaultFontSize));
		*/
	return QFont();
}

void HelpViewer::setViewerFont(const QFont &font)
{
    
    QWebSettings *webSettings = settings();
    webSettings->setFontFamily(QWebSettings::StandardFont, font.family());
    webSettings->setFontSize(QWebSettings::DefaultFontSize, font.pointSize());
}

void HelpViewer::scaleUp()
{
    
    setTextSizeMultiplier(textSizeMultiplier() + 0.1);
}

void HelpViewer::scaleDown()
{
    
    setTextSizeMultiplier(qMax(0.0, textSizeMultiplier() - 0.1));
}

void HelpViewer::resetScale()
{
    
    setTextSizeMultiplier(1.0);
}

qreal HelpViewer::scale() const
{
    
    return textSizeMultiplier();
}

QString HelpViewer::title() const
{
    
    return QWebView::title();
}

void HelpViewer::setTitle(const QString &title)
{
    
    Q_UNUSED(title)
}

QUrl HelpViewer::source() const
{
    
    HelpPage *currentPage = static_cast<HelpPage*> (page());
    if (currentPage && !d->m_loadFinished) {
        // see HelpPage::acceptNavigationRequest(...)
        return currentPage->m_loadingUrl;
    }
    return url();
}

void HelpViewer::setSource(const QUrl &url)
{
    
	QString str=url.toString();
    load(url.toString() == QLatin1String("help") ? LocalHelpFile : url);
}

QString HelpViewer::selectedText() const
{
    
    return QWebView::selectedText();
}

bool HelpViewer::isForwardAvailable() const
{
    
    return pageAction(QWebPage::Forward)->isEnabled();
}

bool HelpViewer::isBackwardAvailable() const
{
    
    return pageAction(QWebPage::Back)->isEnabled();
}

bool HelpViewer::findText(const QString &text, FindFlags flags, bool incremental,
    bool fromSearch)
{
    
    Q_UNUSED(incremental); Q_UNUSED(fromSearch);
    QWebPage::FindFlags options = QWebPage::FindWrapsAroundDocument;
    if (flags & FindBackward)
        options |= QWebPage::FindBackward;
    if (flags & FindCaseSensitively)
        options |= QWebPage::FindCaseSensitively;

    bool found = QWebView::findText(text, options);
    options = QWebPage::HighlightAllOccurrences;
    QWebView::findText(QLatin1String(""), options); // clear first
    QWebView::findText(text, options); // force highlighting of all other matches
    return found;
}

// -- public slots

void HelpViewer::copy()
{
    
    triggerPageAction(QWebPage::Copy);
}

void HelpViewer::forward()
{
    
    QWebView::forward();
}

void HelpViewer::backward()
{
    
    back();
}

// -- protected

void HelpViewer::keyPressEvent(QKeyEvent *e)
{
    
    // TODO: remove this once we support multiple keysequences per command
    if (e->key() == Qt::Key_Insert && e->modifiers() == Qt::CTRL) {
        if (!selectedText().isEmpty())
            copy();
    }
    QWebView::keyPressEvent(e);
}

void HelpViewer::wheelEvent(QWheelEvent *event)
{
    
    if (event->modifiers()& Qt::ControlModifier) {
        event->accept();
        event->delta() > 0 ? scaleUp() : scaleDown();
    } else {
        QWebView::wheelEvent(event);
    }
}

void HelpViewer::mousePressEvent(QMouseEvent *event)
{
    
#ifdef Q_OS_LINUX
    if (handleForwardBackwardMouseButtons(event))
        return;
#endif

    if (HelpPage *currentPage = static_cast<HelpPage*> (page())) {
        currentPage->m_pressedButtons = event->buttons();
        currentPage->m_keyboardModifiers = event->modifiers();
    }

    QWebView::mousePressEvent(event);
}

void HelpViewer::mouseReleaseEvent(QMouseEvent *event)
{
    
#ifndef Q_OS_LINUX
    if (handleForwardBackwardMouseButtons(event))
        return;
#endif

    QWebView::mouseReleaseEvent(event);
}

// -- private slots

void HelpViewer::actionChanged()
{
    
    QAction *a = qobject_cast<QAction *>(sender());
    if (a == pageAction(QWebPage::Copy))
        emit copyAvailable(a->isEnabled());
    else if (a == pageAction(QWebPage::Back))
        emit backwardAvailable(a->isEnabled());
    else if (a == pageAction(QWebPage::Forward))
        emit forwardAvailable(a->isEnabled());
}

// -- private

bool HelpViewer::eventFilter(QObject *obj, QEvent *event)
{
    
    return QWebView::eventFilter(obj, event);
}

void HelpViewer::contextMenuEvent(QContextMenuEvent *event)
{
    
    QWebView::contextMenuEvent(event);
}

QT_END_NAMESPACE
