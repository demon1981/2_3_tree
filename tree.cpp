#include "tree.h"


//****************************************��������������� ������*******************************************************
bool tree::isLeaf(node *curNode)// �������� ��� ���� ��������� ������
{
	return ((curNode->lNode == nullptr) && (curNode->mNode == nullptr) && (curNode->rNode == nullptr));
}

//������� ��������� ��� ��� �������� ���� ��� ������, ���������� ��� �������� ��� ���������������
//
bool tree::isNodeWithLeaf(node * curNode)
{
	return ((curNode->lNode->lNode == nullptr) 
		&& (curNode->mNode->lNode == nullptr) 
		&& (curNode->rNode != nullptr ? curNode->rNode->lNode == nullptr : true));
		//|| (curNode->rNode == nullptr ));
}

void tree::sortNode(node *curNode)
{
	if (curNode->lKey > curNode->rKey)
		swap(curNode);
}

void tree::swap(node * curNode)
{
	int temp = curNode->lKey;
	curNode->lKey = curNode->rKey;
	curNode->rKey = temp;
}

//����� �� ������ ����������� ������ �� �������
//���������� o��������� �� ������� ������, ������� ��� �� ������ 
bool tree::printLevel(size_t level, node *curNode)
{
	//size_t cntLevel = 0;

	bool flagIsLeaf = false;

	if (level)
	{
		--level;
		if (curNode->lNode != nullptr)
		{
			flagIsLeaf = printLevel(level, curNode->lNode);
		}
		if (curNode->mNode != nullptr)
		{
			flagIsLeaf = printLevel(level, curNode->mNode);
		}
		if (curNode->rNode != nullptr)
		{
			flagIsLeaf = printLevel(level, curNode->rNode);
		}
	}
	else//���� �������� �������� ������ ������� �� ������.
	{
		if (curNode->nodeSize == 1)
			std::cout << "(" << curNode->lKey << ")" << "   ";
		else if (curNode->nodeSize == 2)
			std::cout << "(" << curNode->lKey << " - " << curNode->rKey << ")" << "   ";
		flagIsLeaf = isLeaf(curNode);//���� ��� ���� ��������� ���
	}
	return flagIsLeaf;
}

//������ ������ �� �������
void tree::printTree()
{
	size_t level = 0;
	while (!printLevel(level, headNode))
	{
		level++;
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
}

//����� ������ � ������
void tree::printTree2()
{	
	std::deque<std::pair<std::pair<node*, node*>, size_t>> bufer;				//����� ������ ���� ������������ �������� ���� � �������
	bufer.push_back(std::make_pair(std::make_pair(nullptr,headNode), 1));
	size_t currentLevel = 1;

	while (!bufer.empty())
	{
		if (currentLevel != bufer.front().second)
		{
			currentLevel = bufer.front().second;
			std::cout << std::endl;
		}

		node *perentNode = bufer.front().first.first;
		node *curNode = bufer.front().first.second;		
		
		std::cout << "[";
			
		if (perentNode != nullptr)
		{
			std::cout << "(" << perentNode->lKey;
			if (perentNode->nodeSize == 2)
			{
				std::cout << "-" << perentNode->rKey;
			}
			std::cout << ")";
		}

		if (curNode->nodeSize == 1)
			std::cout << curNode->lKey << "]" << "   ";
		else if (curNode->nodeSize == 2)
			std::cout << curNode->lKey << " - " << curNode->rKey << "]" << "   ";

		if (curNode->lNode != nullptr)
			bufer.push_back(std::make_pair(std::make_pair(curNode, curNode->lNode), currentLevel + 1));
		if (curNode->mNode != nullptr)
			bufer.push_back(std::make_pair(std::make_pair(curNode, curNode->mNode), currentLevel + 1));
		if (curNode->rNode != nullptr)
			bufer.push_back(std::make_pair(std::make_pair(curNode, curNode->rNode), currentLevel + 1));

		bufer.pop_front();
	}
	std::cout << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
}

size_t tree::size()
{
	return _size;
}

//������� ��������� ����������� ������ �� ��������� ���������
//�� ������� ������
//�� ���������� ������ � ������: 1 ���� - 2 �����, 2 ����� - 3 �����
bool tree::checkTree()
{
	return checkNode(headNode);
}

bool tree::checkNode(node* curNode)
{
	bool a = true;
	
	//�������� ��� ����� ���� ������ �������
	if (curNode->nodeSize == 2)
	{
		a = a && (curNode->lKey < curNode->rKey);		
	}

	if ( ! isLeaf(curNode) )// ���� ������� ���� �� ����, �� ������� ��� ����������� � ���������� �������� �����
	{		
		//�������� �� ���������� �������� �����
		a = a && (curNode->nodeSize == 1) ? (curNode->lNode != nullptr && curNode->mNode != nullptr && curNode->rNode == nullptr)
			: (curNode->lNode != nullptr && curNode->mNode != nullptr && curNode->rNode != nullptr);
	
		//�������� ��� ����� ����� ������ ����������� ����� �����
		a = a && (curNode->lNode->nodeSize == 2 ? (curNode->lKey > curNode->lNode->lKey && curNode->lKey > curNode->lNode->rKey) : (curNode->lKey > curNode->lNode->lKey));
	
		//�������� ��� ����� ����� ������ ����������� ������� �����
		a = a && (curNode->mNode->nodeSize == 2 ? (curNode->lKey < curNode->mNode->lKey && curNode->lKey < curNode->mNode->rKey) : (curNode->lKey < curNode->mNode->lKey));
		
		if (curNode->nodeSize == 2)
		{
			//�������� �n� ����� ����� ������ ����������� ������� �����
			a = a && (curNode->mNode->nodeSize == 2 ? (curNode->rKey > curNode->mNode->lKey && curNode->rKey > curNode->mNode->rKey) : (curNode->rKey > curNode->mNode->lKey));
	
			//�������� ��� ������ ����� ������ ����������� ������ �����
			a = a && (curNode->rNode->nodeSize == 2 ? (curNode->rKey < curNode->rNode->lKey && curNode->rKey < curNode->rNode->rKey) : (curNode->rKey < curNode->rNode->lKey));		
		}

		a = a && checkNode(curNode->lNode);
		a = a && checkNode(curNode->mNode);
		if (curNode->nodeSize == 2)
		{
			a = a && checkNode(curNode->rNode);
		}

	}
	if (!a)
	{
		std::cout << "Check FALSE!!! " << curNode->lKey << std::endl;
	}

	return a;
}

//****************************************������������*******************************************************
tree::tree() : _size(0), headNode(new node) {}

//****************************************������ �������*******************************************************
//������� ����� ������� ��������
void tree::insert(int value)
{	
	_size++;
	node* splitedNode = nodeInsert(headNode, value);

	if (splitedNode != nullptr)								//������ �� ������, ��������� nodeInsert ������� ���������� �� ������� ����, 
	{														//�������� ��� ��������� ���������, value �������� ������� ����			
		node *newHeadNode = new node;						//������� ����� �������� ����, �������� ���� value ���������� ������ �� ������ �������� ���� � ���������� ����
		
		newHeadNode->nodeSize = 1;
		
		newHeadNode->lKey = value;
		
		newHeadNode->lNode = headNode;
		newHeadNode->mNode = splitedNode;

		this->headNode = newHeadNode;
	}		
}

//������� ������ ����� � ��������� ����
//���� ������� ��������� ������ ��������� nullptr.
//���� ������� ��� ������� ���� �� ����� ���� ���������, �������� ���� ��� ���� ����� ��� ��� �����, 
//���������  ����������� ����, ��� �������� ���� �������� �������� ��������, ������������ ���� ��������� ������� ���� �� ��� ����, 
//� ���������� ��������� ���������� ����� ������� ���������� 
tree::node* tree::nodeInsert(node *nodeForInsert, int &value)
{	
	if ( !(value == nodeForInsert->lKey || value == nodeForInsert->rKey) )//���� ����������� ������� �� ����� �� ������ �����
	{
		if (isLeaf(nodeForInsert))									//���� ���� ��������� ������
		{
			if (nodeForInsert->nodeSize == 2)
			{
				return splitLeaf(nodeForInsert, value);
			}
			else if (nodeForInsert->nodeSize == 1)					//� ���� ���� ���� �������
			{
				nodeForInsert->rKey = value;
				sortNode(nodeForInsert);
				nodeForInsert->nodeSize = 2;
			}
			else if (nodeForInsert->nodeSize == 0)					//���� ������, ��� ������ ������ �������
			{
				nodeForInsert->lKey = value;
				nodeForInsert->nodeSize = 1;
			}
		}
		else														//���� ���� �� ���� �������� �������� ����
		{
			node *nextNode;
			if (value < nodeForInsert->lKey)
			{
				nextNode = nodeForInsert->lNode;
			}
			else if (nodeForInsert->nodeSize == 2 && value > nodeForInsert->rKey)
			{
				nextNode = nodeForInsert->rNode;
			}
			else
			{
				nextNode = nodeForInsert->mNode;
			}

			node* splitedNode = nodeInsert(nextNode, value);		//���� ������� ������ ��������, ������������� ����������� ���� � ����������

			if (splitedNode != nullptr)
			{
				if (nodeForInsert->nodeSize == 1)					//���� � ������� ���� 1 ���� �� ��������� �������� ����� � �������� ����
				{
					if (value > nodeForInsert->lKey)
					{
						nodeForInsert->rKey = value;
						nodeForInsert->rNode = splitedNode;
					}
					else
					{
						nodeForInsert->rKey = nodeForInsert->lKey;
						nodeForInsert->lKey = value;
						nodeForInsert->rNode = nodeForInsert->mNode;
						nodeForInsert->mNode = splitedNode;
					}
					nodeForInsert->nodeSize = 2;
				}
				else												//���� � ���� ��������� ��� ��������, �� � ���� ���� ���������
				{
					return splitNode(nodeForInsert, splitedNode, value);
				}
			}
		}
	}
	return nullptr;
}

//������� ��������� ���������� ����, ���� ��� �������� ��� �����, �� ��� ����, ���������� ���� ����������
tree::node* tree::splitNode(node * nodeForSplit, node * joinNode, int & value)
{
	int midleValue;
	node * newNode = new node;
	//1 ���� ������� ������� � �������� ��������� ���� ��� ������ ������
	if (value < nodeForSplit->lKey)
	{
		midleValue = nodeForSplit->lKey;
		newNode->lKey = nodeForSplit->rKey;
		nodeForSplit->lKey = value;

		newNode->lNode = nodeForSplit->mNode;
		newNode->mNode = nodeForSplit->rNode;
		nodeForSplit->mNode = joinNode;
		nodeForSplit->rNode = nullptr;
	}
	else if (value > nodeForSplit->rKey)
	{
		midleValue = nodeForSplit->rKey;
		newNode->lKey = value;

		newNode->lNode = nodeForSplit->rNode;
		newNode->mNode = joinNode;
		nodeForSplit->rNode = nullptr;
	}
	else
	{
		midleValue = value;
		newNode->lKey = nodeForSplit->rKey;
		
		newNode->mNode = nodeForSplit->rNode;
		newNode->lNode = joinNode;
		nodeForSplit->rNode = nullptr;
	}

	newNode->nodeSize = 1;
	nodeForSplit->nodeSize = 1;
	value = midleValue;

	return newNode;
}

//������� ��������� ���������� ����, ���� ��� �������� ��� �����, �� ��� ����, ���������� ���� ����������
tree::node* tree::splitLeaf(node * nodeForSplit, int & value)
{
	int midleValue;				
	node * newNode = new node;
																//1 ���� ������� ������� � �������� ��������� ���� ��� ������ ������
	if (value < nodeForSplit->lKey)
	{
		midleValue = nodeForSplit->lKey;			
		newNode->lKey = nodeForSplit->rKey;
		nodeForSplit->lKey = value;	
	}
	else if (value > nodeForSplit->rKey)
	{
		midleValue = nodeForSplit->rKey;			
		newNode->lKey = value;
	}
	else
	{
		midleValue = value;
		newNode->lKey = nodeForSplit->rKey;
	}

	newNode->nodeSize = 1;
	nodeForSplit->nodeSize = 1;
	value = midleValue;

	return newNode;
}

//****************************************������ ��������*******************************************************
//�������� ��������:
//1) �������� �� ����� � ����� ����������, ������� ���� �������, ��������� ������.
//2) 
bool tree::eraseNode(node* curNode, int value)
{
	if (isLeaf(curNode))
	{
		if ( curNode->nodeSize == 2)
		{
			if(value == curNode->lKey)							//���� � ���� 2 �����, ��� ������� ������ ������ ������� � ������, ��� ������ ������ ��������� ������ ����
			{
				curNode->lKey = curNode->rKey;			
			}			
			curNode->nodeSize = 1;
			return true;
		}
		else if (curNode->nodeSize == 1)						//���� � ���� ����, ������ ���, �������� ������ � ����, ������ false ����� �������������� ������
		{			
			curNode->nodeSize = 0;
			return false;			
		}
		return true;											//TO-DO ���� ���������� �� ����� �� ��� ����� ������ ���
	}
	else if (curNode->lKey == value || (curNode->nodeSize == 2 && curNode->rKey == value))		//���� ����� ������ � ����
	{		
		if (curNode->lKey == value)								//���� ����� ������ � ����
		{
			bool needDistrib = ! returnKeyFromLeaf(curNode->lNode, value);
			curNode->lKey = value;
			
			if ( needDistrib )
			{
				if ( ! distribNode(curNode, curNode->lNode ))
				{
					mergeNode(curNode, curNode->lNode);
					return false;
				}			
			}
			return true;
		}
		else if (curNode->rKey == value && curNode->nodeSize == 2)
		{
			bool needDistrib = ! returnKeyFromLeaf(curNode->mNode, value);
			curNode->rKey = value;

			if (needDistrib)
			{
				if ( ! distribNode(curNode, curNode->mNode ))
				{
					mergeNode(curNode, curNode->mNode);
					return false;
				}
			}			
			return true;
		} 				
	}
	else													//��������� ����� �� �����
	{
		node* nextNode;
		if (value < curNode->lKey)
		{
			nextNode = curNode->lNode;
		}
		else if (curNode->nodeSize == 2 && value > curNode->rKey)
		{
			nextNode = curNode->rNode;
		}
		else
		{
			nextNode = curNode->mNode;
		}


		if ( ! eraseNode(nextNode, value))						//���� �������� ������� � ��������� ������������
		{
			if ( ! distribNode(curNode, nextNode))				//������� ��������������� �����
			{
				mergeNode(curNode, nextNode);					//���� ����������������� �� ���������� ������� �����
				return false;
			}
		}
		return true;
	}
}

void tree::erase(int value)
{
	eraseNode(headNode, value);
}

//������� ���������������� ���� � ���� ���������:
//1) ���� � ������� - �������� ����� � ������ ������������������ ���� ������ �� 2-3 ���� 1-2 ����.
//2) ���� � ��������� ������:
// - ���� ��� ����� � ����, ������� ���� ���� ���� � ������� � ���� delNode
// - ���� � ���� ���� ���� �� ��� ����� � ������� ��������� ����, �� ���������
//� ������ ���������� ���������������� ���������� false
bool tree::distribNode(node* curNode, node* delNode)
{
	if (isNodeWithLeaf(curNode))//����������������� ��� � �������
	{
		if (delNode == curNode->lNode)							//���������� ������� ����
		{
			if (curNode->mNode->nodeSize == 2 || (curNode->nodeSize == 2 && curNode->rNode->nodeSize == 2))	//���� ���� ����� � 2 ������� ������ ������� �����
			{				
				delNode->lKey = curNode->lKey;
				curNode->lKey = curNode->mNode->lKey;
				delNode->nodeSize = 1;
				if (curNode->mNode->nodeSize == 2)				//��������� ��� ���� ������� 2-3 � 1-2
				{
					curNode->mNode->lKey = curNode->mNode->rKey;
					curNode->mNode->nodeSize = 1;
				}
				else if (curNode->nodeSize == 2 && curNode->rNode->nodeSize == 2)
				{
					curNode->mNode->lKey = curNode->rKey;
					curNode->rKey = curNode->rNode->lKey;
					curNode->rNode->lKey = curNode->rNode->rKey;
					curNode->rNode->nodeSize = 1;
				}
				return true;				
			}
			else if (curNode->nodeSize == 2)				//���� � ���������� ������ �� 1 ����� ������� �� 2-3 ���� 1-2
			{
				curNode->lNode = curNode->mNode;
				curNode->lNode->rKey = curNode->lNode->lKey;
				curNode->lNode->lKey = curNode->lKey;
				curNode->lKey = curNode->rKey;
				curNode->mNode = curNode->rNode;
				curNode->nodeSize = 1;
				curNode->lNode->nodeSize = 2;
				curNode->rNode = nullptr;
				delete delNode;
				return true;
			}
		}
		else if (delNode == curNode->mNode)
		{
			if (curNode->lNode->nodeSize == 2)
			{
				curNode->mNode->lKey = curNode->lKey;
				curNode->lKey = curNode->lNode->rKey;
				curNode->lNode->nodeSize = 1;
				delNode->nodeSize = 1;

				return true;
			}
			else if (curNode->rNode != nullptr && curNode->rNode->nodeSize == 2)
			{
				curNode->mNode->lKey = curNode->rKey;
				curNode->rKey = curNode->rNode->lKey;
				curNode->rNode->lKey = curNode->rNode->rKey;
				curNode->rNode->nodeSize = 1;
				delNode->nodeSize = 1;

				return true;
			}
			else if (curNode->nodeSize == 2)				//���� � ���������� ������ �� 1 ����� ������� �� 2-3 ���� 1-2
			{
				curNode->mNode = curNode->rNode;
				curNode->mNode->rKey = curNode->mNode->lKey;
				curNode->mNode->lKey = curNode->rKey;
				curNode->nodeSize = 1;
				curNode->mNode->nodeSize = 2;
				curNode->rNode = nullptr;
				delete delNode;
				return true;
			}
		}
		else if (delNode == curNode->rNode)
		{
			if (curNode->mNode->nodeSize == 2 && curNode->lNode->nodeSize == 2)
			{
				delNode->lKey = curNode->rKey;
				delNode->nodeSize = 1;
				if (curNode->mNode->nodeSize == 2)
				{
					curNode->rKey = curNode->mNode->rKey;
					curNode->mNode->nodeSize = 1;
				}
				else
				{
					curNode->rKey = curNode->mNode->lKey;
					curNode->mNode->lKey = curNode->lKey;
					curNode->lKey = curNode->lNode->rKey;
					curNode->lNode->nodeSize = 1;
				}
				return true;
			}
			else if (curNode->nodeSize == 2)					//���� � ���������� ������ �� 1 ����� ������� �� 2-3 ���� 1-2
			{
				curNode->mNode->rKey = curNode->rKey;
				curNode->nodeSize = 1;
				curNode->mNode->nodeSize = 2;
				curNode->rNode = nullptr;
				delete delNode;
				return true;
			}
		}
	}
	else//����������������� ���� ��� ������
	{
		if (delNode == curNode->lNode)
		{
			if (curNode->mNode->nodeSize == 2)					//���� ������ ����� ��� �����, �������������� �����
			{
				node* subNode = new node;						//����� �������� ����
				curNode->lNode = subNode;
				subNode->lNode = delNode;						//��������� ����� ������ �� ����� ����
				subNode->lKey = curNode->lKey;					//�������������� �����
				subNode->mNode = curNode->mNode->lNode;			//��������� �������� ���� �� ��������
				subNode->nodeSize = 1;

				curNode->lKey = curNode->mNode->lKey;			//���������� ����� � ���� 
				curNode->mNode->lKey = curNode->mNode->rKey;				
				curNode->mNode->nodeSize = 1;
				curNode->mNode->lNode = curNode->mNode->mNode;
				curNode->mNode->mNode = curNode->mNode->rNode;
				curNode->mNode->rNode = nullptr;
				return true;
			}
			else if(curNode->nodeSize == 2)						//���� ���� ����� ��� ����� � ������� ���, �� ���������� ���� � 1-2
			{
				curNode->mNode->rKey = curNode->mNode->lKey;
				curNode->mNode->lKey = curNode->lKey;
				curNode->mNode->nodeSize = 2;				
				curNode->mNode->rNode = curNode->mNode->mNode;
				curNode->mNode->mNode = curNode->mNode->lNode;
				curNode->mNode->lNode = delNode;

				curNode->lKey = curNode->rKey;
				curNode->nodeSize = 1;
				curNode->lNode = curNode->mNode;
				curNode->mNode = curNode->rNode;
				curNode->rNode = nullptr;
				return true;
			}
		}
		else if (delNode == curNode->mNode)
		{
			if (curNode->lNode->nodeSize == 2)					//���� ����� ������ ����� ��� �����, �������������� �����
			{
				node* subNode = new node;						//����� �������� ����
				curNode->mNode = subNode;

				subNode->mNode = delNode;						//��������� ����� ������ �� ����� ����
				subNode->lKey = curNode->lKey;					//�������������� �����
				subNode->nodeSize = 1;

				subNode->lNode = curNode->lNode->rNode;			//��������� �������� ���� �� ��������
				curNode->lNode->rNode = nullptr;

				curNode->lKey = curNode->lNode->rKey;			//���������� ����� � ���� 				
				curNode->lNode->nodeSize = 1;
								
				return true;
			}
			else if (curNode->nodeSize == 2 && curNode->rNode->nodeSize == 2)	//���� ������ ������� ����� ��� �����, �������������� �����
			{
				node* subNode = new node;						//����� �������� ����
				curNode->mNode = subNode;

				subNode->lNode = delNode;						//��������� ����� ������ �� ����� ����
				subNode->lKey = curNode->rKey;					//�������������� �����
				subNode->nodeSize = 1;

				subNode->mNode = curNode->rNode->lNode;			//��������� �������� ���� �� ��������
				curNode->rNode->lNode = curNode->rNode->mNode;
				curNode->rNode->mNode = curNode->rNode->rNode;
				curNode->rNode->rNode = nullptr;

				curNode->rKey = curNode->rNode->lKey;			//���������� ����� � ���� 				
				curNode->rNode->lKey = curNode->rNode->rKey;
				curNode->rNode->nodeSize = 1;

				return true;
			}
			else if (curNode->nodeSize == 2)					//���� ���� ����� ��� ����� ������� 1 - 2 ����
			{
				node* subNode = new node;						//����� �������� ����
				curNode->mNode = subNode;

				subNode->lNode = delNode;						//��������� ����� ������ �� ����� ����
				subNode->lKey = curNode->rKey;					//������� ����
				subNode->rKey = curNode->rNode->lKey;
				subNode->nodeSize = 2;
				curNode->nodeSize = 1;

				subNode->mNode = curNode->rNode->lNode;			//��������� �������� ���� �� ��������
				subNode->rNode = curNode->rNode->mNode;
				delete curNode->rNode;
				curNode->rNode = nullptr;

				return true;
			}
		}
		else if (delNode == curNode->rNode)
		{
			if (curNode->mNode->nodeSize == 2)
			{
				node* subNode = new node;						//����� �������� ����
				curNode->rNode = subNode;
				subNode->mNode = delNode;						//��������� ����� ������ �� ����� ����
				subNode->lKey = curNode->rKey;					//�������� ������ ���� ����������� ����
				subNode->nodeSize = 1;

				subNode->lNode = curNode->mNode->rNode;			//��������� �������� ������ ���� �� ��������
				curNode->mNode->rNode = nullptr;
				
				curNode->rKey = curNode->mNode->rKey;			//�������� ���� �� �������� ���� � �����������				
				curNode->mNode->nodeSize = 1;				
				
				return true;
			}
			else if (curNode->nodeSize == 2)					//���� ���� ����� ��� ����� � ������� ���, �� ���������� ���� � 1-2
			{
				curNode->mNode->rKey = curNode->rKey;
				curNode->nodeSize = 1;
				curNode->rNode = nullptr;

				curNode->mNode->rNode = delNode;
				curNode->mNode->nodeSize = 2;

				return true;
			}
		}
	}
	return false;
}

//������� ������� ���� �� ����, ��������� ������� ������ ����� �� ����� ������ �� ����� ����
// �������� ��������������� ���� � ������� ������ ����
bool tree::returnKeyFromLeaf(node* curNode, int &value)
{
	if (isLeaf(curNode))
	{
		if (curNode->nodeSize == 1)
		{
			curNode->nodeSize = 0;									
			value = curNode->lKey;
			return false;											//���� ���� � ���� ���� ������ ���� ��� ����������� ����������������� ���� ��� �������
		}
		else if (curNode->nodeSize == 2)
		{
			curNode->nodeSize = 1;
			value = curNode->rKey;
			return true;											//���� ����� � ����� ��� �� ����������������� �� �����
		}
	}	
	else
	{
		node *nextNode = nullptr;
		if (curNode->nodeSize == 1)
		{
			nextNode = curNode->mNode;
		}
		else if (curNode->nodeSize == 2)
		{
			nextNode = curNode->rNode;
		}
		
		//returnKeyFromLeaf(nextNode, value);
		
		if ( ! returnKeyFromLeaf(nextNode, value) )								//���� ���� ����� ��������� ����� ���� ������������� ���� ����
		{
			if ( ! distribNode(curNode, nextNode) )
			{
				mergeNode(curNode, nextNode);
				return false;
			}
		}
		return true;
	}
	return false;
}

//������� ������� ��������� ��� ���� ���� �� ���������� ������� ��� ������ ������������ ��� ���������������� �����
//
bool tree::mergeNode(node* curNode, node* nextNode)
{
	if (nextNode->nodeSize == 0)					//��������� ������� ���� � ������� 
	{
		if (curNode->lNode == nextNode)
		{		
			curNode->rKey = curNode->mNode->lKey;		
			delete curNode->mNode;
		}
		else if (curNode->mNode == nextNode)
		{			
			curNode->rKey = curNode->lKey;
			curNode->lKey = curNode->lNode->lKey; 
			delete curNode->lNode;
		}
		curNode->nodeSize = 2;
		curNode->lNode = nullptr;
		curNode->mNode = nullptr;		
		delete nextNode;		
	}
	else if(nextNode->nodeSize == 2)				//���� ��������������� �� ���������� �� nextNode ��������� ��� ����� ������
	{
		if (curNode->lNode == nextNode)				//��������� ������� ���� � ��������
		{
			node* nodeForMerge = curNode->mNode;

			curNode->rKey = nodeForMerge->lKey;
			curNode->nodeSize = 2;

			curNode->rNode = nodeForMerge->mNode;
			curNode->mNode = nodeForMerge->lNode;
			delete nodeForMerge;
		}
		else if (curNode->mNode == nextNode)
		{
			node* nodeForMerge = curNode->lNode;

			curNode->rKey = curNode->lKey;
			curNode->lKey = nodeForMerge->lKey;
			curNode->nodeSize = 2;

			curNode->rNode = nextNode;
			curNode->lNode = nodeForMerge->lNode;
			curNode->mNode = nodeForMerge->mNode;
			delete nodeForMerge;			
		}		
	}
	return true;
}

//****************************************������ ������*******************************************************
tree::node* tree::findNode(node* curNode,  int value)
{
	if (value == curNode->lKey || (value == curNode->rKey && curNode->nodeSize == 2))
	{
		return curNode;
	}
		
	if (! isLeaf(curNode))
	{
		if ( value < curNode->lKey )
			return findNode(curNode->lNode, value);
		else if ( curNode->nodeSize == 2 && value > curNode->rKey )
			return findNode(curNode->rNode, value);
		else
			return findNode(curNode->mNode, value);
	}
	return nullptr;
}

bool tree::find(int value)
{	
	return findNode(headNode, value) == nullptr ? false: true;	
}