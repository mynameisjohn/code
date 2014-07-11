#include <vector>

class circBuf{
protected:
	std::vector<int> data;
	int idx;
	int dim;
public:
	circBuf(int dim){
		this->dim=dim;
		data.clear();
		data.resize(dim);
		idx=-1;
	}
	inline void add(int x){
		idx = (idx+1)%dim;
		data[idx] = x;
	}
	inline int last(){
		return data[idx];
	}
};
