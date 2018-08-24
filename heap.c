template <class T>
struct Less
{
	bool operator()(const T& left, const T& right)
	{
		return left < right;
	}
};
template <class T>
struct Greater
{
	bool operator()(const T& left, const T& right)
	{
		return right < left;
	}
};
 
template <class T,class Compare=Less<T>>
class Heap
{
public:
	Heap()
		:_array(NULL)
	{}
 
	//创建最小堆--->时间复杂度O(Nlog2N)
	Heap(const T* array, size_t size)
	{
		//将数组中的元素存起来，按照完全二叉树
		for (size_t i = 0; i < size; ++i)
		{
			_array.push_back(array[i]);
		}
		_array.resize(size);//底层用vector搭载，插入元素后调整vector的大小
 
		//找完全二叉树中倒数第一个非叶子结点
		int Root = (size - 2) >> 1;
		for (; Root >= 0; Root--)
			_Adjustdown(Root);//向下调整，从第一个非叶子结点到根结点调整
	}
 
	//插入元素
	void Insert(const T& data)
	{
		_array.push_back(data);
		int size = _array.size();
 
		int Root = (size - 2) >> 1;
		for (; Root >= 0; Root--)
			_Adjustup(Root);//向上调整，从第一个非叶子结点到根结点调整
	}
 
	//删除元素
	void Delete()
	{
		//堆为空
		if (_array.empty())
			return;
 
		//堆中含有一个元素,直接删除
		else if (_array.size() == 1)
		{
			_array.pop_back();
			return;
		}
 
		//堆中含有多个元素
		else
		{
			//1.将最后一个元素与堆顶元素交换
			int size = _array.size();
			swap(_array[0], _array[size - 1]);
 
			//2.删除最后一个元素
			if (!_array.empty())
				_array.pop_back();
 
			//3.从堆顶开始，向下调整
			int Root = (size - 2) >> 1;//找完全二叉树中倒数第一个非叶子结点
			for (; Root >= 0; Root--)
				_Adjustdown(Root);
		}
	}
 
private:
	//向下调整
	void _Adjustdown(size_t pRoot)
	{
		size_t parent = pRoot;
		size_t child = parent * 2 + 1;//默认左孩子为左右孩子中最小的结点
		size_t size = _array.size();//计算堆中元素的个数
 
		//找出左右孩子中最小的结点（小堆）/最大的结点（大堆）
		if ((child + 1 < size) && Compare()(_array[child+1],_array[child]))//首先需要保证右孩子存在
			swap(_array[child], _array[child + 1]);
 
		while (child < size)
		{
			if (Compare()(_array[child], _array[parent]))
			{
				swap(_array[child], _array[parent]);
				parent = child;//继续向下走
				child = parent * 2 + 1;
			}
			else
				break;
		}
	}
 
	//向上调整
	void _Adjustup(size_t pRoot)
	{
		size_t parent = pRoot;
		size_t child = parent * 2 + 1;//默认左孩子为最小孩子
		size_t size = _array.size();
 
		if ((child + 1 < size) && Compare()(_array[child + 1], _array[child]))
			swap(_array[child], _array[child + 1]);
 
		while (child > 0)
		{
			parent = (size - 2) >> 1;
			if (Compare()(_array[child],_array[parent]))
			{
				swap(_array[parent], _array[child]);
				child = parent;//向上继续
				parent = (child - 1) >> 1;
			}
			else
				break;
		}
	}
 
private:
	vector<T> _array;
};
