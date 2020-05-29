#define _CRT_OBSOLETE_NO_WARNINGS
#include <bangtal.h>

#define A 283
#define B 587
#define C 870

SceneID scene1;
ObjectID arr[7], startbutton, endbutton;
TimerID timer1;
int i = 0;
int count = 0;
int a[2] = { 7, A };
int b[2] = { 0, B };
int c[2] = { 0, C };
int arr1[200] = { 0, };
int arr2[200] = { 0, };
int arr3[200] = { 0, };

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown) {

	ObjectID object = createObject(image);

	locateObject(object, scene, x, y);

	if (shown) {
		showObject(object);
	}

	return object;
}

void move(int n, int *from, int *to)
{
	arr1[i] = n - 1;
	if (from[1] == A) arr2[i] = A;
	else if (from[1] == B) arr2[i] = B;
	else if (from[1] == C) arr2[i] = C;
	if (to[1] == A) arr3[i] = A;
	else if (to[1] == B) arr3[i] = B;
	else if (to[1] == C) arr3[i] = C;

	i++;
	count++;
}

void hanoi(int n, int *from, int *by, int *to)
{
	if (n == 1)
		move(n, from, to);
	else
	{
		hanoi(n - 1, from, to, by);
		move(n, from, to);
		hanoi(n - 1, by, from, to);
	}
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {

	if (object == startbutton) {
		hideObject(startbutton);
		hanoi(7, a, c, b);
		i = 0;
		setTimer(timer1, 0.2f);
		startTimer(timer1);
	}

	if (object == endbutton) {
		endGame();
	}
}

void timerCallback(TimerID timer) {

	int* f = 0;
	int* t = 0;

	if (arr2[i] == A) f = a;
	else if (arr2[i] == B) f = b;
	else if (arr2[i] == C) f = c;
	if (arr3[i] == A) t = a;
	else if (arr3[i] == B) t = b;
	else if (arr3[i] == C) t = c;

	locateObject(arr[arr1[i]], scene1, arr3[i], t[0] * 50 + 205);

	f[0]--;
	t[0]++;

	i++;

	if (i != count) {
		setTimer(timer1, 0.2f);
		startTimer(timer1);
	}
	else {
		showObject(endbutton);
	}
	
}

int main()
{
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);

	scene1 = createScene("하노이의 탑", "images/cover1.png");

	startbutton = createObject("images/start.png", scene1, 610, 70, true);
	endbutton = createObject("images/end.png", scene1, 610, 70, false);

	arr[0] = createObject("images/1.png", scene1, 283, 505, true);
	arr[1] = createObject("images/2.png", scene1, 283, 455, true);
	arr[2] = createObject("images/3.png", scene1, 283, 405, true);
	arr[3] = createObject("images/4.png", scene1, 283, 355, true);
	arr[4] = createObject("images/5.png", scene1, 283, 305, true);
	arr[5] = createObject("images/6.png", scene1, 283, 255, true);
	arr[6] = createObject("images/7.png", scene1, 283, 205, true);

	timer1 = createTimer(0.2f);

	startGame(scene1);
}