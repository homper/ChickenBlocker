#define CHICKENBLOCKER_TEST
#include "../src/ChickenBlocker.c"

#include <assert.h>

int main(void) {
	const char *id =
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";
	char line[256];
	struct MeetingOccurrence event;

	snprintf(line, sizeof line, "event=%s,100,200,0\n", id);
	assert(meeting_occurrence_parse(line, &event) == 0);
	assert(strcmp(event.id, id) == 0);
	assert(event.start == 100);
	assert(event.end == 200);
	assert(event.attempted == 0);

	snprintf(line, sizeof line, "event=%s,100,200,1", id);
	assert(meeting_occurrence_parse(line, &event) == 0);
	assert(event.attempted == 1);

	snprintf(line, sizeof line, "event=%s,100,200,0 junk\n", id);
	assert(meeting_occurrence_parse(line, &event) == -1);
	snprintf(line, sizeof line, "event=%s,200,100,0\n", id);
	assert(meeting_occurrence_parse(line, &event) == -1);

	assert(camera_confirms_meeting(1, 1));
	assert(!camera_confirms_meeting(1, 0));
	assert(!camera_confirms_meeting(0, 1));
	assert(!camera_confirms_meeting(-1, 1));

	puts("meeting state regressions: ok");
	return 0;
}
