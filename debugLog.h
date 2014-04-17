#include <stdio.h>

class debugLog
{
public:
	debugLog(void);
	bool openLog(void);
	bool openLog(char *filename);

	void beginTask(char *taskName);
	void endTask(void);

	void writeToLog(char *msg);
	void writeToLog(char *msg, char *p1);
	void writeToLog(char *msg, long p1);
	void writeToLog(char *msg, double p1);

	void closeLog(void);

private:
	FILE *handle;
	int level;

	bool validLog;

	void printTabs(void);
};