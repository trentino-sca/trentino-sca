#ifndef PTHREAD_H
#define PTHREAD_H

#include <boost/thread/thread.hpp>
#include <boost\thread\condition_variable.hpp>
 
#include <QObject>
#include <QApplication>
#include <QEvent>
#include <QWaitCondition>
#include <QMutex>

#include "GuiStart.h"
 
class Application;
class DialogProvider : public QObject
{
  Q_OBJECT
 
  Application *_qtApp;
 
  QWaitCondition _waitCondition;
  QMutex _mutex;
  volatile bool _eventProcessed;
 
  void signalEventProcessed()
    {
      QMutexLocker locker(&_mutex);
      _eventProcessed = true;
      _waitCondition.wakeAll();
    }
 
protected:
  Application *qtApp() const { return _qtApp; }
 
  void customEvent(QEvent *event);
 
public:
  explicit DialogProvider(Application *qtApp, QObject *parent = 0) :
    QObject(parent),
    _qtApp(qtApp),
    _eventProcessed(false) { }
 
  void waitForEventProcessed()
    {
      QMutexLocker locker(&_mutex);
      if (!_eventProcessed)
        _waitCondition.wait(&_mutex);
      _eventProcessed = false;
    }
};
 
class ShowWaitDialogEvent : public QEvent
{
  GWidget _gw;
  Gui_Control *_gc;
 
public:
  explicit ShowWaitDialogEvent(QEvent::Type eventType,
                               GWidget gw, Gui_Control *gc) :
    QEvent(eventType),
    _gw(gw),
	_gc(gc) { }
 
	GWidget gw() const { return _gw ; }
	Gui_Control *gc() const { return _gc ; }
};
 
class Application : public QApplication
{
  DialogProvider *_dpInstance;
 
  static int staticArgc;
  static char staticDummy[];
  static char *staticArgv[2];
 
  QEvent::Type _showMyWidgetEventType;
 
protected:
  virtual DialogProvider *createDialogProvider(Application *app)
    { return new DialogProvider(app,this); }
 
public:
  explicit Application();
 
  DialogProvider *dpInstance();
 
  QEvent::Type showMyWidgetEventType() const { return _showMyWidgetEventType; }
 
  QEvent *createShowMyWidgetEvent(GWidget gw, Gui_Control *gc) const
    { return new ShowWaitDialogEvent(showMyWidgetEventType(), gw, gc); }
};
 
class ThreadedApplication
{
  Application *_app;
  volatile bool _started;
  boost::mutex _dialogMutex;
  boost::mutex _waitForApplicationRunningMutex;
  boost::condition_variable _applicationRunningCondition;
 
protected:
  Application *qtApp() const { return _app; }
 
  virtual Application *createApplication() { return new Application(); }
 
  boost::mutex &dialogMutex() { return _dialogMutex; }
 
public:
  explicit ThreadedApplication() :
    _app(nullptr),
    _started(false) { }
 
  virtual ~ThreadedApplication() { stop(); }
 
  void operator()()
    {
      if (!_app)
      {
        boost::unique_lock< boost::mutex > guard(_waitForApplicationRunningMutex);
 
        _app = createApplication();
        _app->dpInstance();
        _started = true;
        _applicationRunningCondition.notify_all();
      }
 
      _app->exec();
    }
 
  void waitForApplicationRun()
    {
      boost::unique_lock< boost::mutex > guard(_waitForApplicationRunningMutex);
      if (!_started)
        _applicationRunningCondition.wait(guard);
    }
 
  void stop()
    {
      if (_app)
        _app->quit();
    }
 
  void showMyWidget(GWidget gw, Gui_Control *gc)
    {
      if (_app)
      {
        _app->postEvent(_app->dpInstance(),_app->createShowMyWidgetEvent(gw, gc));
        _app->dpInstance()->waitForEventProcessed();
      }
    }
};
 
#endif