#ifndef MINHEAP_TCC_
#define MINHEAP_TCC_

#include <vector>
#include <climits>

template <class T> class HeapElement{
public:
	int priority;
	T element;
	HeapElement(T elementIn,int priorityIn);
    HeapElement(){}

};

template <class T> class MinHeap{
	std::vector< HeapElement<T> > heap;
	inline int Father(int pos);
	inline int Left(int pos);
	inline int Right(int pos);
public:
	void MinHeapify(int pos);
    void DecreaseKey(int pos, int key);
    void Insert(T element, int key);
	HeapElement<T> Extract();
	bool Empty();
    int SearchOnHeap(T elem, HeapElement<T>* &structure ,bool (*Comparator)(void*, void*) );
};






/** #########################################################################################
 ######################################### Methods' Definition ###########################
########################################################################################**/





template <class T>
HeapElement<T>::HeapElement(T elementIn,int priorityIn): element(elementIn), priority(priorityIn){}

template <class T>
inline int MinHeap<T>::Father(int pos){
	return (pos - 1)/2;
}
template <class T>
inline int MinHeap<T>::Left(int pos){
	return 2*pos + 1;
}

template <class T>
inline int MinHeap<T>::Right(int pos){
	return 2*pos + 2;
}

template <class T>
void MinHeap<T>::MinHeapify(int pos){
	int l = Left(pos);
	int r = Right(pos);
	int smallest = pos;

	if(l < heap.size() && heap[smallest].priority > heap[l].priority)
		smallest = l;

	if(r < heap.size() && heap[smallest].priority > heap[r].priority)
		smallest = r;
	
	if(smallest != pos){
		HeapElement<T> aux(heap[pos]);
		heap[pos] = heap[smallest];
		heap[smallest] = aux;
		MinHeapify(smallest);
	}		
}

template <class T>
void MinHeap<T>::DecreaseKey(int pos, int key){
    if(key < heap[pos].priority){
        heap[pos].priority = key;
        while(pos > 0 && heap[Father(pos)].priority > heap[pos].priority){
            HeapElement<T> aux(heap[pos]);
            heap[pos] = heap[Father(pos)];
            heap[Father(pos)] = aux;
            pos = Father(pos);
        }
    };
}
template <class T>
void MinHeap<T>::Insert(T element, int key) {
    heap.push_back(HeapElement<T>(element, INT_MAX ));
    DecreaseKey(heap.size() - 1, key);
}
template <class T>
HeapElement<T> MinHeap<T>::Extract() {
    HeapElement<T> max(heap[0]);
    heap[0] = heap[heap.size()-1];
    heap.erase(heap.end());
    MinHeapify(0);
    return max;
}

template <class T>
bool MinHeap<T>::Empty() {
	return heap.empty();
}

template <class T>
int MinHeap<T>::SearchOnHeap(T elem, HeapElement<T>* &structure, bool (*Comparator)(void*, void*) ) {
	int i;
	for(i = 0; i < heap.size(); i++){
		if( Comparator( (void*) &elem, (void*) &(heap[i].element) ) ) {
            structure = &heap[i];
            return i;
        }
	}
    structure = nullptr;
	return -1;
}


#endif //MINHEAP_TCC_
