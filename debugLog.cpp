#include "DebugLog.h"

DebugLog *DebugLog::mSelf = 0;

DebugLog *DebugLog::self()
{
  if( !mSelf )
    mSelf = new DebugLog();

  return mSelf;
}

DebugLog::DebugLog() : m_level(0)
{
  mSelf = this;
}

void DebugLog::openLog()
{
  openLog( "debug.log" );
}

void DebugLog::openLog( const string &filename )
{
  self()->m_outfile.open( filename.c_str() );

  self()->writeToLog( "<RCTGLLog>\n" );

  self()->m_level = 1;
}

void DebugLog::printTabs()
{
  for( int i = 0; i < self()->m_level; i++ )
    self()->m_outfile << "\t";
}

void DebugLog::beginTask( const string &taskName )
{
  self()->printTabs();

  self()->m_outfile << "<TASK NAME='" << taskName << "'>" << endl;

  self()->m_level++;
}

void DebugLog::endTask()
{
  self()->m_level--;

  self()->printTabs();

  self()->m_outfile << "</TASK>" << endl;
}

void DebugLog::writeToLog(const string &msg)
{
  //self()->writeToLog( msg, string() );
  self()->printTabs();
  self()->m_outfile << msg << endl;
}

/*static void DebugLog::writeToLog(const string &msg, const string &p1)
{
  self()->printTabs();
  self()->m_outfile << msg << ": " << p1 << endl;
	if(validLog)
	{
		printTabs();
		fprintf(handle, msg, p1);
		fflush(handle);
	}
}

void debugLog::writeToLog(char *msg, long p1)
{
	if(validLog)
	{
		printTabs();
		fprintf(handle, msg, p1);
		fflush(handle);
	}
}

void debugLog::writeToLog(char *msg, double p1)
{
	if(validLog)
	{
		printTabs();
		fprintf(handle, msg, p1);
		fflush(handle);
	}
}*/

void DebugLog::closeLog()
{
  self()->m_outfile << "</RCTGLLog> " << endl;
  self()->m_outfile.close();
  /*	if(validLog)
	{
		fprintf(handle, "</RCTGLLog>\n");
		fflush(handle);
		fclose(handle);

		validLog = false;
		}*/
}
