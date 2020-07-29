/*
1. 异或理解，位运算
一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字
	相同数据异或, 就是0
	任何数据和0异或, 就是本身
	1. 整体异或, 最终的结果一定是不同数据的异或, 结果一定不为0
	2. x !=0  --> 一定有比特位为1, 不同的两个数据, 异或之后该位置的比特位一定是不同的
	3. 假设是第n个, 根据遍历数组检测每一个数字的第n个位, 根据是否为1, 将其分组为A,B
	4. 凡是相同的数据, 一定在同一组, 不同的数据,一定在不同的组
	5. 结论: A or B
*/
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	void FindNumsAppearOnce(vector<int> data, int* num1, int *num2) {// 数组,要拿出去的两个数字
		if (num1 == nullptr || num2 == nullptr){
			return;
		}
		// 整体异或, 结果为两个不相同的数据异或之后的值,
		int result = data[0];
		for (auto it = data.begin() + 1; it != data.end(); it++){
			result ^= *it;
		}
		// 防止题出错, 判断一下
		if (result == 0)
			return;
		// 挨个检测比特位, 找结果比特位中的1(两个不同数据不同的比特位) 从低到高
		int flag = 1; // 8个比特位 最后一个比特位为1
		int size = sizeof(int)* 8;
		int i = 0;
		while (size--){// 控制循环次数
			// 用flag按位与result, 检测最低位, 与0相&就变0了,(只有对应的两个二进位都为1时，结果位才为1), 其他情况都为0, 相当于把检测位之外的其他位全都清0了, 
			if ((flag << i) & result){// 挨个位检查
				// 如果结果不为0. 说明该位为1, 找到不相同的位了
				// 但是flag左移不影响flag的原值(就相当于加法 但不是+=),这里也需要改变flag的值
				flag <<= i;
				break;
			}
			i++;
		}
	/*	for (int i = 0;i < size; i++){ 
			if ((flag << i) & result){
				flag <<= i; 
				break;
			}
		}*/

		// 根据输出的flag可看出异或之后的结果的哪些比特位为1,
		// 分组
		*num1 = 0;
		*num2 = 0;
		for (int i = 0; i < data.size(); i++){
			if (data[i] & flag){// 对应比特位为1的
				// A组 
				*num1 ^= data[i];// 再次分组整体异或, 最终只留下单独的那个数
			}
			else{// 对应比特位为0的
				// B组
				*num2 ^= data[i];
			}
		}

	}
};


/*
2. 场景转化为模型，滑动窗口
小明很喜欢数学,有一天他在做数学作业时,要求计算出9~16的和,他马上就写出了正确答案是100。但是
他并不满足于此,他在想究竟有多少种连续的正数序列的和为100(至少包括两个数)。没多久,他就得到另
一组连续正数和为100的序列:18,19,20,21,22。现在把问题交给你,你能不能也很快的找出所有和为S的
连续正数序列? Good Luck!
输出所有和为S的连续正数序列。序列内按照从小至大的顺序，序列间按照开始数字从小到大的顺序
	
	序列一定是连续且等差的, 且公差为1
	隐含条件就是序列最大值不会大于正数和
	动态调整范围
	扩大区间--->high++
	缩小区间--->low++
*/
#include <vector>
#include <iostream>
using namespace std;
class Solution {
public: 
	vector<vector<int>> FindContinuousSequence(int sum) {
		vector<vector<int>> result;
		//不考虑负数情况 
		//定义两个位置，表示其实和结束，start和end之间就是一段连续递增的序列 
		//两个起点，相当于动态窗口的两边，根据其窗口内的值的和来确定窗口的位置和大小 
		//采用闭区间[low, high]方式进行解决
		int low = 1;
		int high = 2;
		
		while (low < high){// 至少两个数据, 所以low不能等于high, 当大于sum后, high不变, 而low一直++ 最终肯定会大于high
			// 由于是连续的，差为1的一个序列，那么求和公式是(a0+an)*n/2
			// 这里的low和high不光代表位置，也代表对应的值
			int total = (low + high)*(high - low + 1) / 2;// 求和

			// 比较
			if (sum == total){
				// 找到了一组序列中的数据和符合要求
				vector<int> temp;
				for (int i = low; i <= high; i++){
					temp.push_back(i);
				}
				result.push_back(temp);
				// 这里要保证拿到一个序列之后(至此一个,独一无二)，下一个序列(短)只能从下一个数据开始
				// 而high会自动调节
				low++;
			}
			else if (total < sum){
				// 说明该序列区间中的数据和小于sum，应该扩大区间,以包含更多数据
				high++;
			}
			else{// total > sum
				// 说明该序列区间中的数据和大于sum，应该缩小区间,以包含较少数据
				low++;
			}
		}
		return result;
	}
};

/*
3. 字符串逆置，循环次数去重
汇编语言中有一种移位指令叫做循环左移（ROL），现在有个简单的任务，就是用字符串模拟这个指令的运算结果。对于一个给定的字符序列S，请你把其循环左移K位后的序列输出。例如，字符序列S=”abcXYZdef”,要求输出循环左移3位后的结果，即“XYZdefabc”。是不是很简单？OK，搞定它！

	有效左移次数 < 字符串长度 ===> num %= length
	局部逆置
	双倍串
*/
// 双循环
class Solution{ 
public:
	void LeftRotateStringOne(string &str){
		// 把字符串左旋一次
		char c = str[0];// 先把第一个元素保存, 其他前移
		int len = str.size();
		// 左旋
		int i = 0;
		for (int i = 0; i < len - 1; i++){// i最大到i-1, i最大到len-2, 后面的元素就是len-1
			// 把后面(大)的值往前(小)放
			str[i] = str[i + 1];
		}
		// i= len-1, i的下标已经是最后一个位置
		str[i] = c;
	}
	string LeftRotateString(string str, int n){
		if (str.empty() || n < 0){
			return str;
		}
		int step = n % str.size();// 字符串长度不用担心为0了, 去重
		for (int i = 0; i < step; i++){
			LeftRotateStringOne(str);
		}
		return str;
	}
};
// 时间复杂度O(N)
class Solution{
public:
	void Reverse(string& str, int start, int end){// 闭区间
		while (start < end){
			// 头尾交换
			char temp = str[start];
			str[start] = str[end];
			str[end] = temp;
			++start;
			--end;
		}
	}
	string LeftRotateString2(string str, int n){
		// 123abc 先对123逆置, 在对abc逆置, 再整体
		if (str.empty() || n < 0){
			return str;
		}
		int step = n % str.size();
		// 逆置, 闭区间[]
		Reverse(str, 0, step - 1);// 下标从0开始, 前半部分字符串长度的个数
		Reverse(str, step, str.size() - 1);
		Reverse(str, 0, str.size() - 1);
		
		return str;
	}
};

/*
2. 子串划分，子串逆置
公司最近来了一个新员工Fish，每天早晨总是会拿着一本英文杂志，写些句子在本子上。同事Cat对Fish写的内容颇感兴趣，有一天他向Fish借来翻看，但却读不懂它的意思。例如，“student. a am I”。后来才意识到，这家伙原来把句子单词的顺序翻转了，正确的句子应该是“I am a student.”。Cat对一一翻转的这些单词顺序可不在行，你能帮助他么？
	
	字符串单个局部逆置
	字符串整体逆置

*/

class Solution {
public:
	void Reverse(string& str, int start, int end){
		while (start < end){
			char temp = str[start];
			str[start] = str[end];
			str[end] = temp;
			start++;
			end--;
		}
	}
	string ReverseSentence(string str) {
		if (str.size() == 0){
			return str;
		}
		// 碰到空格停下,
		int i = 0;
		int j = i;
		int len = str.size();
		while (i < len){
			// 判断空格
			while (i < len && !isspace(i)){
				i++;//让i一直往后走，碰到第一个空格
			}
			Reverse(str, 0, i-1);//逆置当前有效子串
			while (i < len && isspace(i)){
				i++;//过滤所有空格，指向下一个有效子串的开始
			}
			// 接下来肯定是合法字符
			j = i; // 都指向了最后一个字符 保存当前的位置
		}
		// 走到这里，一定是 i == str.size()了，但是最后一个有效子串并没有被逆置, 逆置之
		Reverse(str, j, i - 1);// 逆置最后一个字符串
		Reverse(str, 0, len - 1);// 整体逆置

		return str;
	}
};

/*
3. 树遍历，stack，queue结合使用
请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右至左的顺序打印，第三行按照从左到右的顺序打印，其他行以此类推。

	层序(用queue)
	逆序(stack) 栈只有一个出口,
	当前层是从左向右, 下层就是从左向右入栈(先进后出), 弹栈时就是从右向左了
	当前层是从右向左(边访问边入栈) 下层就是从右向左入栈(先进后出), 弹栈时就是从左向右了
*/
#include <stack>
#include <queue>
struct TreeNode {
	int val; 
	struct TreeNode *left;
	struct TreeNode *right; 
	TreeNode(int x) : val(x), left(NULL), right(NULL) { 
	}
};
class Solution {
public:
	// 如果当前层是以从左向右的顺序访问, 下一层的每个节点入栈的顺序, 和当前层的访问顺序一致
	// 边访问, 边入栈
	vector<vector<int>> Print(TreeNode* pRoot) {// 二维数组
		// 方向标志位
		vector<vector<int>> result;
		if (pRoot == nullptr){
			return result;
		}
		stack<TreeNode*> st;// 保存要遍历的节点
		queue<TreeNode*> q;// 作为临时队列来进行辅助
		int dir = 1;// 1代表从左到右, 2代表从右向左
		vector<int> v;// 用来保存一次的结果
		st.push(pRoot);// 放入首节点
		// 层序访问, 出这个循环就是把当前层的结点都访问完了(出栈了).同时也把下一层的结点也全部都放在队列里等入栈了
		while (!st.empty()){// 如果树上还有未访问的结点, 那栈就不会为空
			while (!st.empty()){// 就一直弹栈
				TreeNode* cur = st.top();// 拿到当前结点
				st.pop();// 弹出来, 题要求是返回形式, 就不打印了
				// 访问当前层, 最终要求的结果是vector<int>
				v.push_back(cur->val);// 保存当前值到临时结果

				// 拿节点的次序和入栈的/访问的方向是一致的
				// 从左向右访问, 从左向右入栈,先拿左子树; 否则就是从右向左访问,则从右向左入栈,先拿右子树
				TreeNode* first = (dir == 1) ? cur->left : cur->right;// 先入栈,
				// 从左向右访问, 左子树已经被拿过来了,这里就拿右子树; 否则就是从右向左访问,则从右向左入栈, 则拿左子树
				TreeNode* second = (dir == 1) ? cur->right : cur->left;// 后入栈.

				// 上面完成了"之"字打印, 下面完成层序遍历
				// (下一层的)结点已经拿出来了, 先暂时存到队列里.
				if (first != nullptr){// 入谁, 把当前的结点入到队列(先进先出), 
					q.push(first);
				}
				if (second != nullptr){
					q.push(second);
				}
			}
			result.push_back(v);// 把访问到的值全都放到返回值里
			// 再把刚才保存的所有结点(在队列中)重新导到栈里(放到栈里(先进后出)后,等到访问的时候,刚好就是逆序访问了)
			while (!q.empty()){
				st.push(q.front());
				q.pop();
			}
			v.clear();// 内部数据清空
			dir = (dir == 1) ? 2 : 1;// 改变访问方向, 为下一次访问做准备
		}
		return result;
	}
};

/*
4. BST有序性理解
给定一棵二叉搜索树，请找出其中的第k小的结点。例如， （5，3，7，2，4，6，8） 中，按结点数值大小顺序第三小结点的值为4
	
	BST本身就是有序的(左子树小于根结点, 右子树大于根结点)，中序遍历即是升序 
	要求第k小，即中序遍历时到达第k个元素(二叉搜索树，不存在两个相同的节点值) 
	采用循环中序遍历的方式(不使用递归), 拿到一个根结点, 先把所有的左节点压栈(通过根结点得到左节点,访问完左节点,才访问根结点--->根结点先进后出---> 选栈结构)
	中序采用do{..}while()语句, 先让他执行一次,先把所有结点全入栈(以一个根结点出发的所有左节点)

	在搜素二叉树中, 中序找第k个结点
*/
struct TreeNode { 
	int val; 
	struct TreeNode *left; 
	struct TreeNode *right; 
	TreeNode(int x) : val(x), left(NULL), right(NULL) { 
	}
};
class Solution {
public: 
	TreeNode* KthNode(TreeNode* pRoot, int k) { 
		// 第k小(k越大,则值越大的)，那就从k开始, k是总结点个数 
		if(pRoot == nullptr || k <= 0){
			return nullptr; 
		}
		stack<TreeNode*> st; // 放节点
		TreeNode* node = pRoot;
		do{
			while(node != nullptr){ // node指向第一个结点
				// 将左子树全部入栈, 先放根,再放左节点, 最后出栈的时候就是先出最左结点
				st.push(node);
				node = node->left;
			}
			// 把当前结点的所有的左子树全入了, 此时结点肯定指向nullptr, 接下来开始中序访问
			if(!st.empty()){ 
				node = st.top();// 保存栈顶元素
				st.pop();// 已访问了一次
				k--;// 则k--
				if(k == 0){// 说明已经把对应的结点找到了
					return node; 
					//其实是最大的那个结点, 也就是第k小, 输入的k就代表结点总数, 那么第k小就是倒数第几个最大的
				}// 访问完左子树
				node = node->right;// 压右子树, 下次循环时,又把这个结点的所有左节点全入栈了
			}
		}while (node != nullptr || !st.empty());// 说明当前的树是没有访问完的
		//node有可能为空(没有右节点)，但是只要stack不为空，就要继续pop求下一个。
		//有没有可能st为空？有可能(刚入了一个结点,发现其没有左子树,当前结点出栈之后, 栈就为空了,但是节点不为空)，这个时候就要检测node，如果node不为空，就要整体检测右子树 
		
		//走到这里，就说明没有找到 
		return nullptr;
	}
};