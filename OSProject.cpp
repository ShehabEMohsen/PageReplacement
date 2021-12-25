#include <iostream>

using namespace std;

void FIFO(int pages[], int pageNum, int frames, int frame[]) {
	int x, y;
	int pagefaults = 0;
	for (int i = 0;i < frames;i++) {
		frame[i] = -1;
	}
	y = 0;
	for (int i = 0; i < pageNum; i++) {

		x = 0;
		for (int j = 0; j < frames; j++) {
			if (frame[j] == pages[i]) {
				x = 1;
			}
		}
		if (x == 0) {
			frame[y] = pages[i];
			y = (y + 1) % frames;
			pagefaults++;


		}


	}
	cout << "Final frame: ";
	for (int j = 0;j < frames;j++) {
		cout << frame[j] << " ";
	}
	cout << "\n Page fault = " << pagefaults;

}

void LRU(int pageNum, int pages[], int frames) {
	int queue[20], x = 0, pagefaults = 0, c1, c2[20], b[20];
	queue[x] = pages[x];
	pagefaults++;x++;
	for (int i = 1;i < pageNum;i++) {
		c1 = 0;
		for (int j = 0;j < frames;j++) {
			if (pages[i] != queue[j])
				c1++;
		}
		if (c1 == frames) {
			pagefaults++;
			if (x < frames) {
				queue[x] = pages[i];
				x++;
			}
			else {
				for (int k = 0;k < frames; k++) {
					c2[k] = 0;
					for (int j = i - 1;j < pageNum;j--) {
						if (queue[k] != pages[j])
							c2[k]++;
						else
							break;
					}
				}
				for (int k = 0; k < frames; k++)
					b[k] = c2[k];
				for (int k = 0;k < frames; k++) {
					for (int j = k;j < frames;j++) {
						if (b[k] < b[j]) {
							int temp = b[k];
							b[k] = b[j];
							b[j] = temp;
						}
					}
				}
				for (int k = 0; k < frames; k++) {
					if (c2[k] == b[0])
						queue[k] = pages[i];
				}
			}
		}
	}
	cout << "\nFinal frame: ";
	for (int j = 0;j < frames;j++) {
		cout << queue[j] << " ";
	}
	cout << "\nPage faults = " << pagefaults;
}

void Optimal(int pageNum, int frame[], int pages[], int frames) {
	int f1, f2, f3, position, pagefaults = 0;
	int temp[20];
	for (int i = 0; i < pageNum; i++) {
		f1 = f2 = 0;
		for (int j = 0; j < pageNum; j++) {
			if (frame[j] == pages[i]) {
				f1 = f2 = 1;
				break;
			}
		}
		if (f1 == 0) {
			for (int j = 0;j < frames;j++) {
				if (frame[j] == -1) {
					pagefaults++;
					frame[j] = pages[i];
					f2 = 1;
					break;
				}
			}
		}
		if (f2 == 0) {
			f3 = 0;
			for (int j = 0;j < frames;j++) {
				temp[j] = -1;
				for (int k = i + 1;k < pageNum;k++) {
					if (frame[j] == pages[k]) {
						temp[j] = k;
						break;
					}
				}
			}
			for (int j = 0;j < frames;j++) {
				if (temp[j] == -1) {
					position = j;
					f3 = 1;
					break;
				}
			}
			if (f3 == 0) {
				int max = temp[0];
				position = 0;
				for (int j = 1;j < frames;j++) {
					if (temp[j] > max) {
						max = temp[j];
						position = j;
					}
				}
			}
			frame[position] = pages[i];
			pagefaults++;
		}

	}
	cout << "\nFinal frame is ( ";
	for (int j = 0;j < frames;j++) {
		cout << frame[j] << " ";
	}
	cout << ")";
	cout << "\nPage faults = " << pagefaults;
}


int main() {
	int pageNum, pages[30], frames, frame[50], methods;
	char answer;

	cout << "Enter number of pages: ";
	cin >> pageNum;

	cout << "Enter the numbers: ";
	for (int i = 0; i < pageNum; i++) {
		cin >> pages[i];
	}
	cout << "Enter the number of frames: ";
	cin >> frames;

	do {
		cout << "please choose from the following methods" << endl;
		cout << "1) FIFO" << endl;
		cout << "2) LRU" << endl;
		cout << "3) Optimal" << endl;
		cin >> methods;

		if (methods == 1) {
			FIFO(pages, pageNum, frames, frame);
			break;
		}
		else if (methods == 2) {
			LRU(pageNum, pages, frames);
			break;
		}
		else if (methods == 3) {
			Optimal(pageNum, frame, pages, frames);
			break;
		}
	} while (true);
}
