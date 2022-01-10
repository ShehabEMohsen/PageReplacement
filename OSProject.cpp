#include <iostream>

using namespace std;

//FIFO Function
void FIFO(int pages[], int pageNum, int frames, int frame[]) {
	int x, y;
	int pagefaults = 0;

	//Filling the frames with -1 to declare them as empty

	for ( int i = 0 ; i < frames ; i++) {
		frame[i] = -1;
	}

	//y is the variable I use to insert values into the frames
	y = 0;

	
	for (int i = 0 ; i < pageNum ; i++) {
		//x checks if frame is available  0->available  1->not available
		x = 0;

		for (int j = 0 ; j < frames ; j++) {
			if (frame[j] == pages[i]) {
				x = 1;
			}
		}
		if (x == 0) {
			frame[y] = pages[i];
			//if y=5 and I have 5 frames, when I reach frame 5 
			// the mod helps me go back to frame 1 and etc.
			y = (y + 1) % frames;

			//Increase page faults number
			pagefaults++;


		}


	}

	//Printing the final frames
	cout << "Final frames: ";
	for (int j = 0;j < frames;j++) {
		cout << frame[j] << " ";
	}
	//Print page faults value
	cout << "\nPage fault = " << pagefaults;

}



//LRU Function
void LRU(int pageNum, int pages[], int frames) {
	int queue[20], x = 0, pagefaults = 0, c1, c2[20], b[20];

	//insert the first value of the inserted numbers
	//into the first frame in my array
	queue[x] = pages[x];

	//then increase page fault and the counter for indexes
	pagefaults++;x++;

	//start the loop from 1 since we already 
	//inserted the first value (index 0)
	for (int i = 1 ; i < pageNum ; i++) {
		c1 = 0;
		

		//Update the c1 counter related to if the frames are empty or not
		for (int j = 0 ; j < frames ; j++) {
			if (pages[i] != queue[j])
				c1++;
		}

		//pagefaults=5, x counter=3, c1=3

		//To check if number to enter exists already in my frames
		if (c1 == frames) {
			
			pagefaults++;//5

			//to fill empty frames in the start
			if (x < frames) {
				queue[x] = pages[i];
				x++;
			}
			else {//enters else when x counter >= frame number (LRU Algorithm)

				//Check which frame has the LRU number
				// (greatest number in c2 array)
				for (int k = 0 ; k < frames ; k++) {
					c2[k] = 0;
					for (int j = i - 1;j < pageNum;j--) {//  c2 [0,2,1]
						if (queue[k] != pages[j])
							c2[k]++;
						else
							break;
					}
				}
				//Fill another array with the elements of c2
				for (int k = 0 ; k < frames ; k++)
					b[k] = c2[k];
				//3 4 5 2 6

				//2 4 5


				//Sort b array in descending order to later swap out the LRU number
				for (int k = 0 ; k < frames ; k++) {//b[2,1,0]  c2[0,2,1]
					for (int j = k ; j < frames ;j++) {
						if (b[k] < b[j]) {
							int temp = b[k];
							b[k] = b[j];
							b[j] = temp;
						}
					}
				}

				//Swapping out the LRU number with the 
				//new number occurs
				for (int k = 0 ; k < frames ; k++) {
					if (c2[k] == b[0])
						queue[k] = pages[i]; //2 6 5
				}
			}
		}
	}

	//Printing the final frames
	cout << "\nFinal frame: ";
	for (int j = 0;j < frames;j++) {
		cout << queue[j] << " ";
	}
	//Print page faults value
	cout << "\nPage faults = " << pagefaults;
}


//Optimal Function
void Optimal(int pageNum, int frame[], int pages[], int frames) {
	int f1, f2, f3, position, pagefaults = 0;

	//temporary array with a random size to fit the numbers
	int temp[20];

	//The big loop that runs through 
	//the numbers the user enters
	for (int i = 0; i < pageNum; i++) {
		f1 = f2 = 0;
		//3 4 5 2 6

		//-1 -1 -1
		//Small loop to check if the number
		//queued to be inserted exists in frames
		for (int j = 0; j < frames; j++) {
			if (frame[j] == pages[i]) {
				f1 = 1;
				f2 = 1;
				break;
			}
		}
		if (f1 == 0) {
			for (int j = 0;j < frames;j++) {

				if (frame[j] == -1) {//If the frame is empty, fill it with the element queued
					frame[j] = pages[i];
					pagefaults++;
					f2 = 1;
					break;
				}
			}
		}
		//Optimal starts here
		if (f2 == 0) {
			f3 = 0;
			for (int j = 0;j < frames;j++) {//Fill frames with -1 to show they are empty
				temp[j] = -1;
				for (int k = i + 1;k < pageNum;k++) {
					if (frame[j] == pages[k]) {
						temp[j] = k; //Fill the temporary array with the priority of each number
						break;
					}
				}
			}
			//Check if any frames are empty
			for (int j = 0 ; j < frames ; j++) {
				if (temp[j] == -1) {
					f3 = 1;
					position = j;
					break;
				}
			}
			//f3 is the identicator that the frames aren't empty
			//0 -> no frame is empty    1 -> at least one frame is empty
			if (f3 == 0) {
				int max = temp[0];
				position = 0;
				for (int j = 1 ; j < frames ; j++) {
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

	//Printing the final frames
	cout << "\nFinal frame is ( ";
	for (int j = 0;j < frames;j++) {
		cout << frame[j] << " ";
	}
	cout << ")";

	//Print page faults number
	cout << "\nPage faults = " << pagefaults;
}


int main() {
	int pageNum, pages[30], frames, frame[50], methods, answer;

	//infinite loop to repeat the question
	do {
		cout << "Enter number of pages: ";
		cin >> pageNum;

		cout << "Enter the numbers: ";
		for (int i = 0; i < pageNum; i++) {
			cin >> pages[i];
		}
		cout << "Enter the number of frames: ";
		cin >> frames;

		cout << endl;

		cout << "please choose from the following methods" << endl << endl;
		cout << "1) FIFO" << endl;
		cout << "2) LRU" << endl;
		cout << "3) Optimal" << endl;
		cout << "4) Exit" << endl << endl;
		cin >> methods;
		cout << endl;

		//FIFO Function
		if (methods == 1) {
			FIFO(pages, pageNum, frames, frame);
			cout << endl << endl;
			cout << "do you want to continue?" << endl;
			cout << "1) Yes" << endl;
			cout << "2) No" << endl << endl;
			cin >> answer;
			cout << endl;
			if (answer == 1) {
				continue;
			}
			else if (answer == 2) {
				cout << "Thank You, have a good day." << endl;
				break;
			}
		}

		//LRU Function
		else if (methods == 2) {
			LRU(pageNum, pages, frames);
			cout << endl << endl;
			cout << "do you want to continue?" << endl;
			cout << "1) Yes" << endl;
			cout << "2) No" << endl;
			cin >> answer;
			cout << endl;
			if (answer == 1) {
				continue;
			}
			else if (answer == 2) {
				cout << "Thank You, have a good day." << endl;
				break;
			}
		}

		//Optimal Function
		else if (methods == 3) {
			Optimal(pageNum, frame, pages, frames);
			cout << endl << endl;
			cout << "do you want to continue?" << endl;
			cout << "1) Yes" << endl;
			cout << "2) No" << endl;
			cin >> answer;
			cout << endl;
			if (answer == 1) {
				continue;
			}
			else if (answer == 2) {
				cout << "Thank You, have a good day." << endl;
				break;
			}
		}
		else if (methods == 4) {
			cout << "Thank You, have a good day." << endl;
			break;
		}
	} while (true);

}
