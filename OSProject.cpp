#include <iostream>

using namespace std;

void FIFO(int pages[],int pageNum, int frames, int frame[]) {
	int x,y;
	int pagefaults = 0;
	for (int i = 0;i < frames;i++) {
		frame[i] = -1;	
	}
	y = 0;
	for ( int i = 0 ; i < pageNum ; i++ ) {
		
		x = 0;
		for (int j = 0 ; j < frames ; j++) {
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
		cout << frame[j]<<" ";
	}
	cout << "\n Page fault = " << pagefaults;

}

void LRU(int pageNum, int pages[], int frames) {
	int queue[20], x = 0, pagefaults = 0,c1,c2[20],b[20];
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
				for (int k = 0;k < frames; k++ ) {
					c2[k] = 0;
					for (int j = i - 1;j < pageNum;j--) {
						if (queue[k] != pages[j])
							c2[k]++;
						else
							break;
					}
				}
				for ( int k = 0 ; k < frames ; k++ )
					b[k] = c2[k];
				for (int k = 0;k < frames ; k++) {
					for (int j = k;j < frames;j++) {
						if (b[k] < b[j]) {
							int temp = b[k];
							b[k] = b[j];
							b[j] = temp;
						}
					}
				}
				for (int k = 0; k < frames ; k++) {
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


int main() {
	int pageNum, pages[30],frames, frame[50];
	cout << "Enter number of pages: ";
	cin >> pageNum;
	cout << "Enter the numbers: ";
	for ( int i = 0 ; i < pageNum ; i++ ) {
		cin >> pages[i];
	}
	cout << "Enter the number of frames: ";
	cin >> frames;
	//FIFO(pages, pageNum, frames, frame);
	LRU(pageNum,pages,frames);
	return 0;
}
