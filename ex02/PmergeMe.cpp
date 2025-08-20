#include "PmergeMe.hpp"

void PmergeMe::parseInput(int argc, char** argv) {
    if (argc < 2) {
        throw InvalidInputException();
    }
    
    for (int i = 1; i < argc; i++) {
        std::string arg(argv[i]);
        
        if (!isValidNumber(arg)) {
            throw InvalidInputException();
        }
        int num;
        std::stringstream ss(arg);
        ss >> num;
        if (num <= 0) {
            throw InvalidInputException();
        }
        _vectorContainer.push_back(num);
        _dequeContainer.push_back(num);
    }
    
    if (_vectorContainer.empty()) {
        throw InvalidInputException();
    }
}

void PmergeMe::sortAndDisplay() {
    std::cout << "Before: ";
    for (size_t i = 0; i < _vectorContainer.size() && i < 10; i++) {
        std::cout << _vectorContainer[i] << " ";
    }
    if (_vectorContainer.size() > 10) {
        std::cout << "[...]";
    }
    std::cout << std::endl;
    
    std::vector<int> vectorCopy = _vectorContainer;
    double startTime = getCurrentTime();
    fordJohnsonSort(vectorCopy);
    double endTime = getCurrentTime();
    double vectorTime = endTime - startTime;

    std::deque<int> dequeCopy = _dequeContainer;
    startTime = getCurrentTime();
    fordJohnsonSort(dequeCopy);
    endTime = getCurrentTime();
    double dequeTime = endTime - startTime;
    
    std::cout << "After:  ";
    for (size_t i = 0; i < vectorCopy.size() && i < 10; i++) {
        std::cout << vectorCopy[i] << " ";
    }
    if (vectorCopy.size() > 10) {
        std::cout << "[...]";
    }
    std::cout << std::endl;
    std::cout << "Time to process a range of " << _vectorContainer.size() 
              << " elements with std::vector : " << std::fixed << std::setprecision(5) 
              << vectorTime << " us" << std::endl;
    std::cout << "Time to process a range of " << _dequeContainer.size() 
              << " elements with std::deque  : " << std::fixed << std::setprecision(5)
              << dequeTime << " us" << std::endl;
}

bool PmergeMe::isValidNumber(const std::string& str) const {
    if (str.empty()) return false;
    
    size_t start = 0;
    if (str[0] == '+') start = 1;
    if (str[0] == '-') return false;
    
    if (start == str.length()) return false;
    
    for (size_t i = start; i < str.length(); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    
    return true;
}

double PmergeMe::getCurrentTime() const {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000.0 + tv.tv_usec);
}
void PmergeMe::fordJohnsonSort(std::vector<int>& container) {
    if (container.size() <= 1) return;
    mergeInsertSort(container, 0, container.size() - 1);
}

void PmergeMe::mergeInsertSort(std::vector<int>& container, int start, int end) {
    if (end - start <= 10) {
        insertionSort(container, start, end);
        return;
    }
    
    int mid = start + (end - start) / 2;
    mergeInsertSort(container, start, mid);
    mergeInsertSort(container, mid + 1, end);
    std::vector<int> temp(end - start + 1);
    int i = start, j = mid + 1, k = 0;
    
    while (i <= mid && j <= end) {
        if (container[i] <= container[j]) {
            temp[k++] = container[i++];
        } else {
            temp[k++] = container[j++];
        }
    }
    
    while (i <= mid) temp[k++] = container[i++];
    while (j <= end) temp[k++] = container[j++];
    
    for (int i = 0; i < k; i++) {
        container[start + i] = temp[i];
    }
}

void PmergeMe::insertionSort(std::vector<int>& container, int start, int end) {
    for (int i = start + 1; i <= end; i++) {
        int key = container[i];
        int j = i - 1;
        
        while (j >= start && container[j] > key) {
            container[j + 1] = container[j];
            j--;
        }
        container[j + 1] = key;
    }
}

void PmergeMe::fordJohnsonSort(std::deque<int>& container) {
    if (container.size() <= 1) return;
    mergeInsertSort(container, 0, container.size() - 1);
}

void PmergeMe::mergeInsertSort(std::deque<int>& container, int start, int end) {
    if (end - start <= 10) {
        insertionSort(container, start, end);
        return;
    }
    
    int mid = start + (end - start) / 2;
    mergeInsertSort(container, start, mid);
    mergeInsertSort(container, mid + 1, end);
    
    std::deque<int> temp(end - start + 1);
    int i = start, j = mid + 1, k = 0;
    
    while (i <= mid && j <= end) {
        if (container[i] <= container[j]) {
            temp[k++] = container[i++];
        } else {
            temp[k++] = container[j++];
        }
    }
    
    while (i <= mid) temp[k++] = container[i++];
    while (j <= end) temp[k++] = container[j++];
    
    for (int i = 0; i < k; i++) {
        container[start + i] = temp[i];
    }
}

void PmergeMe::insertionSort(std::deque<int>& container, int start, int end) {
    for (int i = start + 1; i <= end; i++) {
        int key = container[i];
        int j = i - 1;
        
        while (j >= start && container[j] > key) {
            container[j + 1] = container[j];
            j--;
        }
        container[j + 1] = key;
    }
}