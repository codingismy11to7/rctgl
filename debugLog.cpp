#include "DebugLog.h"

DebugLog *DebugLog::m_instance = 0;

DebugLog::DebugLog() : m_level(0)
{
  m_instance = this;
}

void DebugLog::openLog()
{
  openLog( "debug.log" );
}

void DebugLog::openLog( const string &filename )
{
  instance()->m_outfile.open( filename.c_str() );

  instance()->writeToLog( "<RCTGLLog>\n" );

  instance()->m_level = 1;
}

void DebugLog::printTabs()
{
  for( int i = 0; i < instance()->m_level; i++ )
    instance()->m_outfile << "\t";
}

void DebugLog::beginTask( const string &taskName )
{
  instance()->printTabs();

  instance()->m_outfile << "<TASK NAME='" << taskName << "'>" << endl;

  instance()->m_level++;
}

void DebugLog::endTask()
{
  instance()->m_level--;

  instance()->printTabs();

  instance()->m_outfile << "</TASK>" << endl;
}

void DebugLog::writeToLog(const string &msg)
{
  //instance()->writeToLog( msg, string() );
  instance()->printTabs();
  instance()->m_outfile << msg << endl;
}

/*static void DebugLog::writeToLog(const string &msg, const string &p1)
{
  instance()->printTabs();
  instance()->m_outfile << msg << ": " << p1 << endl;
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
  instance()->m_outfile << "</RCTGLLog> " << endl;
  instance()->m_outfile.close();
  /*	if(validLog)
	{
		fprintf(handle, "</RCTGLLog>\n");
		fflush(handle);
		fclose(handle);

		validLog = false;
		}*/
}
