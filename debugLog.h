#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class DebugLog
{
public:
  static DebugLog *self();

  static void openLog();
  static void openLog( const string &filename );

  static void beginTask( const string &taskName );
  static void endTask();

  static void writeToLog( const string &msg );
  /*static void writeToLog( const string &msg, const string &p1 );
  static void writeToLog( const string &msg, long p1 );
  static void writeToLog( const string &msg, double p1 );*/

  static void closeLog();

 protected:
  DebugLog();
  static DebugLog *mSelf;

private:
  ofstream m_outfile;
  int m_level;

  void printTabs();
};
