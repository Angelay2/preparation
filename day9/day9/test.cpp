/*
1. �����⣬λ����
һ�����������������������֮�⣬���������ֶ����������Ρ���д�����ҳ�������ֻ����һ�ε�����
	��ͬ�������, ����0
	�κ����ݺ�0���, ���Ǳ���
	1. �������, ���յĽ��һ���ǲ�ͬ���ݵ����, ���һ����Ϊ0
	2. x !=0  --> һ���б���λΪ1, ��ͬ����������, ���֮���λ�õı���λһ���ǲ�ͬ��
	3. �����ǵ�n��, ���ݱ���������ÿһ�����ֵĵ�n��λ, �����Ƿ�Ϊ1, �������ΪA,B
	4. ������ͬ������, һ����ͬһ��, ��ͬ������,һ���ڲ�ͬ����
	5. ����: A or B
*/
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	void FindNumsAppearOnce(vector<int> data, int* num1, int *num2) {// ����,Ҫ�ó�ȥ����������
		if (num1 == nullptr || num2 == nullptr){
			return;
		}
		// �������, ���Ϊ��������ͬ���������֮���ֵ,
		int result = data[0];
		for (auto it = data.begin() + 1; it != data.end(); it++){
			result ^= *it;
		}
		// ��ֹ�����, �ж�һ��
		if (result == 0)
			return;
		// ����������λ, �ҽ������λ�е�1(������ͬ���ݲ�ͬ�ı���λ) �ӵ͵���
		int flag = 1; // 8������λ ���һ������λΪ1
		int size = sizeof(int)* 8;
		int i = 0;
		while (size--){// ����ѭ������
			// ��flag��λ��result, ������λ, ��0��&�ͱ�0��,(ֻ�ж�Ӧ����������λ��Ϊ1ʱ�����λ��Ϊ1), ���������Ϊ0, �൱�ڰѼ��λ֮�������λȫ����0��, 
			if ((flag << i) & result){// ����λ���
				// ��������Ϊ0. ˵����λΪ1, �ҵ�����ͬ��λ��
				// ����flag���Ʋ�Ӱ��flag��ԭֵ(���൱�ڼӷ� ������+=),����Ҳ��Ҫ�ı�flag��ֵ
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

		// ���������flag�ɿ������֮��Ľ������Щ����λΪ1,
		// ����
		*num1 = 0;
		*num2 = 0;
		for (int i = 0; i < data.size(); i++){
			if (data[i] & flag){// ��Ӧ����λΪ1��
				// A�� 
				*num1 ^= data[i];// �ٴη����������, ����ֻ���µ������Ǹ���
			}
			else{// ��Ӧ����λΪ0��
				// B��
				*num2 ^= data[i];
			}
		}

	}
};


/*
2. ����ת��Ϊģ�ͣ���������
С����ϲ����ѧ,��һ����������ѧ��ҵʱ,Ҫ������9~16�ĺ�,�����Ͼ�д������ȷ����100������
�����������ڴ�,�����뾿���ж������������������еĺ�Ϊ100(���ٰ���������)��û���,���͵õ���
һ������������Ϊ100������:18,19,20,21,22�����ڰ����⽻����,���ܲ���Ҳ�ܿ���ҳ����к�ΪS��
������������? Good Luck!
������к�ΪS�������������С������ڰ��մ�С�����˳�����м䰴�տ�ʼ���ִ�С�����˳��
	
	����һ���������ҵȲ��, �ҹ���Ϊ1
	�������������������ֵ�������������
	��̬������Χ
	��������--->high++
	��С����--->low++
*/
#include <vector>
#include <iostream>
using namespace std;
class Solution {
public: 
	vector<vector<int>> FindContinuousSequence(int sum) {
		vector<vector<int>> result;
		//�����Ǹ������ 
		//��������λ�ã���ʾ��ʵ�ͽ�����start��end֮�����һ���������������� 
		//������㣬�൱�ڶ�̬���ڵ����ߣ������䴰���ڵ�ֵ�ĺ���ȷ�����ڵ�λ�úʹ�С 
		//���ñ�����[low, high]��ʽ���н��
		int low = 1;
		int high = 2;
		
		while (low < high){// ������������, ����low���ܵ���high, ������sum��, high����, ��lowһֱ++ ���տ϶������high
			// �����������ģ���Ϊ1��һ�����У���ô��͹�ʽ��(a0+an)*n/2
			// �����low��high�������λ�ã�Ҳ�����Ӧ��ֵ
			int total = (low + high)*(high - low + 1) / 2;// ���

			// �Ƚ�
			if (sum == total){
				// �ҵ���һ�������е����ݺͷ���Ҫ��
				vector<int> temp;
				for (int i = low; i <= high; i++){
					temp.push_back(i);
				}
				result.push_back(temp);
				// ����Ҫ��֤�õ�һ������֮��(����һ��,��һ�޶�)����һ������(��)ֻ�ܴ���һ�����ݿ�ʼ
				// ��high���Զ�����
				low++;
			}
			else if (total < sum){
				// ˵�������������е����ݺ�С��sum��Ӧ����������,�԰�����������
				high++;
			}
			else{// total > sum
				// ˵�������������е����ݺʹ���sum��Ӧ����С����,�԰�����������
				low++;
			}
		}
		return result;
	}
};

/*
3. �ַ������ã�ѭ������ȥ��
�����������һ����λָ�����ѭ�����ƣ�ROL���������и��򵥵����񣬾������ַ���ģ�����ָ���������������һ���������ַ�����S���������ѭ������Kλ���������������磬�ַ�����S=��abcXYZdef��,Ҫ�����ѭ������3λ��Ľ��������XYZdefabc�����ǲ��Ǻܼ򵥣�OK���㶨����

	��Ч���ƴ��� < �ַ������� ===> num %= length
	�ֲ�����
	˫����
*/
// ˫ѭ��
class Solution{ 
public:
	void LeftRotateStringOne(string &str){
		// ���ַ�������һ��
		char c = str[0];// �Ȱѵ�һ��Ԫ�ر���, ����ǰ��
		int len = str.size();
		// ����
		int i = 0;
		for (int i = 0; i < len - 1; i++){// i���i-1, i���len-2, �����Ԫ�ؾ���len-1
			// �Ѻ���(��)��ֵ��ǰ(С)��
			str[i] = str[i + 1];
		}
		// i= len-1, i���±��Ѿ������һ��λ��
		str[i] = c;
	}
	string LeftRotateString(string str, int n){
		if (str.empty() || n < 0){
			return str;
		}
		int step = n % str.size();// �ַ������Ȳ��õ���Ϊ0��, ȥ��
		for (int i = 0; i < step; i++){
			LeftRotateStringOne(str);
		}
		return str;
	}
};
// ʱ�临�Ӷ�O(N)
class Solution{
public:
	void Reverse(string& str, int start, int end){// ������
		while (start < end){
			// ͷβ����
			char temp = str[start];
			str[start] = str[end];
			str[end] = temp;
			++start;
			--end;
		}
	}
	string LeftRotateString2(string str, int n){
		// 123abc �ȶ�123����, �ڶ�abc����, ������
		if (str.empty() || n < 0){
			return str;
		}
		int step = n % str.size();
		// ����, ������[]
		Reverse(str, 0, step - 1);// �±��0��ʼ, ǰ�벿���ַ������ȵĸ���
		Reverse(str, step, str.size() - 1);
		Reverse(str, 0, str.size() - 1);
		
		return str;
	}
};

/*
2. �Ӵ����֣��Ӵ�����
��˾�������һ����Ա��Fish��ÿ���糿���ǻ�����һ��Ӣ����־��дЩ�����ڱ����ϡ�ͬ��Cat��Fishд�������ĸ���Ȥ����һ������Fish������������ȴ������������˼�����磬��student. a am I������������ʶ������һ�ԭ���Ѿ��ӵ��ʵ�˳��ת�ˣ���ȷ�ľ���Ӧ���ǡ�I am a student.����Cat��һһ��ת����Щ����˳��ɲ����У����ܰ�����ô��
	
	�ַ��������ֲ�����
	�ַ�����������

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
		// �����ո�ͣ��,
		int i = 0;
		int j = i;
		int len = str.size();
		while (i < len){
			// �жϿո�
			while (i < len && !isspace(i)){
				i++;//��iһֱ�����ߣ�������һ���ո�
			}
			Reverse(str, 0, i-1);//���õ�ǰ��Ч�Ӵ�
			while (i < len && isspace(i)){
				i++;//�������пո�ָ����һ����Ч�Ӵ��Ŀ�ʼ
			}
			// �������϶��ǺϷ��ַ�
			j = i; // ��ָ�������һ���ַ� ���浱ǰ��λ��
		}
		// �ߵ����һ���� i == str.size()�ˣ��������һ����Ч�Ӵ���û�б�����, ����֮
		Reverse(str, j, i - 1);// �������һ���ַ���
		Reverse(str, 0, len - 1);// ��������

		return str;
	}
};

/*
3. ��������stack��queue���ʹ��
��ʵ��һ����������֮���δ�ӡ������������һ�а��մ����ҵ�˳���ӡ���ڶ��㰴�մ��������˳���ӡ�������а��մ����ҵ�˳���ӡ���������Դ����ơ�

	����(��queue)
	����(stack) ջֻ��һ������,
	��ǰ���Ǵ�������, �²���Ǵ���������ջ(�Ƚ����), ��ջʱ���Ǵ���������
	��ǰ���Ǵ�������(�߷��ʱ���ջ) �²���Ǵ���������ջ(�Ƚ����), ��ջʱ���Ǵ���������
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
	// �����ǰ�����Դ������ҵ�˳�����, ��һ���ÿ���ڵ���ջ��˳��, �͵�ǰ��ķ���˳��һ��
	// �߷���, ����ջ
	vector<vector<int>> Print(TreeNode* pRoot) {// ��ά����
		// �����־λ
		vector<vector<int>> result;
		if (pRoot == nullptr){
			return result;
		}
		stack<TreeNode*> st;// ����Ҫ�����Ľڵ�
		queue<TreeNode*> q;// ��Ϊ��ʱ���������и���
		int dir = 1;// 1���������, 2�����������
		vector<int> v;// ��������һ�εĽ��
		st.push(pRoot);// �����׽ڵ�
		// �������, �����ѭ�����ǰѵ�ǰ��Ľ�㶼��������(��ջ��).ͬʱҲ����һ��Ľ��Ҳȫ�������ڶ��������ջ��
		while (!st.empty()){// ������ϻ���δ���ʵĽ��, ��ջ�Ͳ���Ϊ��
			while (!st.empty()){// ��һֱ��ջ
				TreeNode* cur = st.top();// �õ���ǰ���
				st.pop();// ������, ��Ҫ���Ƿ�����ʽ, �Ͳ���ӡ��
				// ���ʵ�ǰ��, ����Ҫ��Ľ����vector<int>
				v.push_back(cur->val);// ���浱ǰֵ����ʱ���

				// �ýڵ�Ĵ������ջ��/���ʵķ�����һ�µ�
				// �������ҷ���, ����������ջ,����������; ������Ǵ����������,�����������ջ,����������
				TreeNode* first = (dir == 1) ? cur->left : cur->right;// ����ջ,
				// �������ҷ���, �������Ѿ����ù�����,�������������; ������Ǵ����������,�����������ջ, ����������
				TreeNode* second = (dir == 1) ? cur->right : cur->left;// ����ջ.

				// ���������"֮"�ִ�ӡ, ������ɲ������
				// (��һ���)����Ѿ��ó�����, ����ʱ�浽������.
				if (first != nullptr){// ��˭, �ѵ�ǰ�Ľ���뵽����(�Ƚ��ȳ�), 
					q.push(first);
				}
				if (second != nullptr){
					q.push(second);
				}
			}
			result.push_back(v);// �ѷ��ʵ���ֵȫ���ŵ�����ֵ��
			// �ٰѸղű�������н��(�ڶ�����)���µ���ջ��(�ŵ�ջ��(�Ƚ����)��,�ȵ����ʵ�ʱ��,�պþ������������)
			while (!q.empty()){
				st.push(q.front());
				q.pop();
			}
			v.clear();// �ڲ��������
			dir = (dir == 1) ? 2 : 1;// �ı���ʷ���, Ϊ��һ�η�����׼��
		}
		return result;
	}
};

/*
4. BST���������
����һ�ö��������������ҳ����еĵ�kС�Ľ�㡣���磬 ��5��3��7��2��4��6��8�� �У��������ֵ��С˳�����С����ֵΪ4
	
	BST������������(������С�ڸ����, ���������ڸ����)����������������� 
	Ҫ���kС�����������ʱ�����k��Ԫ��(������������������������ͬ�Ľڵ�ֵ) 
	����ѭ����������ķ�ʽ(��ʹ�õݹ�), �õ�һ�������, �Ȱ����е���ڵ�ѹջ(ͨ�������õ���ڵ�,��������ڵ�,�ŷ��ʸ����--->������Ƚ����---> ѡջ�ṹ)
	�������do{..}while()���, ������ִ��һ��,�Ȱ����н��ȫ��ջ(��һ������������������ڵ�)

	�����ض�������, �����ҵ�k�����
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
		// ��kС(kԽ��,��ֵԽ���)���Ǿʹ�k��ʼ, k���ܽ����� 
		if(pRoot == nullptr || k <= 0){
			return nullptr; 
		}
		stack<TreeNode*> st; // �Žڵ�
		TreeNode* node = pRoot;
		do{
			while(node != nullptr){ // nodeָ���һ�����
				// ��������ȫ����ջ, �ȷŸ�,�ٷ���ڵ�, ����ջ��ʱ������ȳ�������
				st.push(node);
				node = node->left;
			}
			// �ѵ�ǰ�������е�������ȫ����, ��ʱ���϶�ָ��nullptr, ��������ʼ�������
			if(!st.empty()){ 
				node = st.top();// ����ջ��Ԫ��
				st.pop();// �ѷ�����һ��
				k--;// ��k--
				if(k == 0){// ˵���Ѿ��Ѷ�Ӧ�Ľ���ҵ���
					return node; 
					//��ʵ�������Ǹ����, Ҳ���ǵ�kС, �����k�ʹ���������, ��ô��kС���ǵ����ڼ�������
				}// ������������
				node = node->right;// ѹ������, �´�ѭ��ʱ,�ְ��������������ڵ�ȫ��ջ��
			}
		}while (node != nullptr || !st.empty());// ˵����ǰ������û�з������
		//node�п���Ϊ��(û���ҽڵ�)������ֻҪstack��Ϊ�գ���Ҫ����pop����һ����
		//��û�п���stΪ�գ��п���(������һ�����,������û��������,��ǰ����ջ֮��, ջ��Ϊ����,���ǽڵ㲻Ϊ��)�����ʱ���Ҫ���node�����node��Ϊ�գ���Ҫ������������ 
		
		//�ߵ������˵��û���ҵ� 
		return nullptr;
	}
};