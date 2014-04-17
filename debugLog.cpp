#include "debugLog.h"

debugLog::debugLog(void)
{
	validLog = false;
	handle = NULL;
	level = 0;
}


bool debugLog::openLog(void)
{
	return openLog("debug.log");
}

bool debugLog::openLog(char *filename)
{
	handle = fopen(filename, "wt");

	if(handle == NULL)
	{
		printf("bad log opening\n");
		validLog = false;
		return false;
	}
	
	validLog = true;

	writeToLog("<XML>\n");

	level = 1;
	
	return true;
}

void debugLog::printTabs(void)
{
	if(validLog)
		for(int i=0; i<level; i++)
			fprintf(handle, "\t");
}

void debugLog::beginTask(char *taskName)
{
	printTabs();

	if(validLog)
		fprintf(handle, "<TASK NAME='%s'>\n", taskName);

	level++;
}

void debugLog::endTask(void)
{
	level--;

	printTabs();

	if(validLog)
		fprintf(handle, "</TASK>\n");
}

void debugLog::writeToLog(char *msg)
{
	writeToLog(msg, (char *)NULL);
}

void debugLog::writeToLog(char *msg, char *p1)
{
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
}

void debugLog::closeLog(void)
{
	if(validLog)
	{
		fprintf(handle, "</XML>\n");
		fflush(handle);
		fclose(handle);

		validLog = false;
	}
}