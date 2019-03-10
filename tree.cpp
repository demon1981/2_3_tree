#include "tree.h"


//****************************************Вспомогательные методы*******************************************************
bool tree::isLeaf(node *curNode)// Проверка что узел являеться листом
{
	return ((curNode->lNode == nullptr) && (curNode->mNode == nullptr) && (curNode->rNode == nullptr));
}

//Функция проверяет что все дочернии узлы это листья, необходимо для проверки при пераспределении
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

//вывод на печать содержимого дерева по уровням
//рекурсивно oпускаемся до нужного уровня, выводим его на печать 
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
	else//если достигли нулевого уровня выводим на печать.
	{
		if (curNode->nodeSize == 1)
			std::cout << "(" << curNode->lKey << ")" << "   ";
		else if (curNode->nodeSize == 2)
			std::cout << "(" << curNode->lKey << " - " << curNode->rKey << ")" << "   ";
		flagIsLeaf = isLeaf(curNode);//если это лист вовращаем лож
	}
	return flagIsLeaf;
}

//печать дерева по уровням
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

//обход дерева в ширину
void tree::printTree2()
{	
	std::deque<std::pair<std::pair<node*, node*>, size_t>> bufer;				//буфер хранит пару родительский дочерний узел и глубину
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

//Функция проверяет коректность дерева по следующим кретериям
//по порядку ключей
//по количеству ключей и ветвей: 1 ключ - 2 ветви, 2 ключа - 3 ветви
bool tree::checkTree()
{
	return checkNode(headNode);
}

bool tree::checkNode(node* curNode)
{
	bool a = true;
	
	//проверка что левый ключ меньше правого
	if (curNode->nodeSize == 2)
	{
		a = a && (curNode->lKey < curNode->rKey);		
	}

	if ( ! isLeaf(curNode) )// если текущий узел не лист, то сравним его содержимого с содержимым дочерних узлов
	{		
		//проверка по количеству дочерних узлов
		a = a && (curNode->nodeSize == 1) ? (curNode->lNode != nullptr && curNode->mNode != nullptr && curNode->rNode == nullptr)
			: (curNode->lNode != nullptr && curNode->mNode != nullptr && curNode->rNode != nullptr);
	
		//проверка что левый ключь больше содержимого левой ветви
		a = a && (curNode->lNode->nodeSize == 2 ? (curNode->lKey > curNode->lNode->lKey && curNode->lKey > curNode->lNode->rKey) : (curNode->lKey > curNode->lNode->lKey));
	
		//проверка что левый ключь меньше содержимого средней ветви
		a = a && (curNode->mNode->nodeSize == 2 ? (curNode->lKey < curNode->mNode->lKey && curNode->lKey < curNode->mNode->rKey) : (curNode->lKey < curNode->mNode->lKey));
		
		if (curNode->nodeSize == 2)
		{
			//проверка чnо правй ключь больше содержимого средней ветви
			a = a && (curNode->mNode->nodeSize == 2 ? (curNode->rKey > curNode->mNode->lKey && curNode->rKey > curNode->mNode->rKey) : (curNode->rKey > curNode->mNode->lKey));
	
			//проверка что правый ключь меньше содержимого правой ветви
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

//****************************************Конструкторы*******************************************************
tree::tree() : _size(0), headNode(new node) {}

//****************************************Методы вставки*******************************************************
//внешний метод вставки элемента
void tree::insert(int value)
{	
	_size++;
	node* splitedNode = nodeInsert(headNode, value);

	if (splitedNode != nullptr)								//всавка не прошла, процедура nodeInsert вернула отделенную от голоной Ноду, 
	{														//головная уже разделена правильно, value содержит средний ключ			
		node *newHeadNode = new node;						//создаем новую головную ноду, помещаем туда value прицепляем ссылки на старую головную ноду и отделенную ноду
		
		newHeadNode->nodeSize = 1;
		
		newHeadNode->lKey = value;
		
		newHeadNode->lNode = headNode;
		newHeadNode->mNode = splitedNode;

		this->headNode = newHeadNode;
	}		
}

//Вставка нового ключа в следующий узел
//Если вставка произошла удачно вовращаем nullptr.
//если вставка для текщего узла не может быть выполенна, например лист или узел имеет уже два ключа, 
//разделяем  возвращаяем ноду, для текущего узла выбираем среденее значение, относительно него разделяем текущий узел на два узла, 
//в параметрах процедуры возвращаем новую среднюю переменную 
tree::node* tree::nodeInsert(node *nodeForInsert, int &value)
{	
	if ( !(value == nodeForInsert->lKey || value == nodeForInsert->rKey) )//если вставляемый элемент не равен ни одному ключу
	{
		if (isLeaf(nodeForInsert))									//если нода являеться листом
		{
			if (nodeForInsert->nodeSize == 2)
			{
				return splitLeaf(nodeForInsert, value);
			}
			else if (nodeForInsert->nodeSize == 1)					//в ноде есть один элемент
			{
				nodeForInsert->rKey = value;
				sortNode(nodeForInsert);
				nodeForInsert->nodeSize = 2;
			}
			else if (nodeForInsert->nodeSize == 0)					//нода пустая, для случае первой вставки
			{
				nodeForInsert->lKey = value;
				nodeForInsert->nodeSize = 1;
			}
		}
		else														//если нода не лист выбираем дочернюю ноду
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

			node* splitedNode = nodeInsert(nextNode, value);		//если вставка прошла неудачно, возвращаеться разделенная нода и переменная

			if (splitedNode != nullptr)
			{
				if (nodeForInsert->nodeSize == 1)					//если в текущей ноде 1 ключ то правильно разнесем ключи и дочерние узлы
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
				else												//если у ноды заполнено два элемента, то её тоже нада разделить
				{
					return splitNode(nodeForInsert, splitedNode, value);
				}
			}
		}
	}
	return nullptr;
}

//Функция разделяет переданную ноду, если она содержит два ключа, на две ноды, отделенную ноду возвращяет
tree::node* tree::splitNode(node * nodeForSplit, node * joinNode, int & value)
{
	int midleValue;
	node * newNode = new node;
	//1 ищем средний элимент и разделем правильно ноды для кажого случая
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

//Функция разделяет переданную ноду, если она содержит два ключа, на две ноды, отделенную ноду возвращяет
tree::node* tree::splitLeaf(node * nodeForSplit, int & value)
{
	int midleValue;				
	node * newNode = new node;
																//1 ищем средний элимент и разделем правильно ноды для кажого случай
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

//****************************************Методы удаления*******************************************************
//Варианты удаления:
//1) Удаление из листа с двумя элементами, удаляем один элемент, уменьшаем размер.
//2) 
bool tree::eraseNode(node* curNode, int value)
{
	if (isLeaf(curNode))
	{
		if ( curNode->nodeSize == 2)
		{
			if(value == curNode->lKey)							//если в узле 2 ключа, при уделени левого меняем местами с правым, для правго просто уменьшаем размер узла
			{
				curNode->lKey = curNode->rKey;			
			}			
			curNode->nodeSize = 1;
			return true;
		}
		else if (curNode->nodeSize == 1)						//ключ в узле один, удалим его, поставим размер в ноль, вернем false чтобы сбалансировать дерево
		{			
			curNode->nodeSize = 0;
			return false;			
		}
		return true;											//TO-DO если переменную не нашли то все равно вернем тру
	}
	else if (curNode->lKey == value || (curNode->nodeSize == 2 && curNode->rKey == value))		//если ключь найден в узле
	{		
		if (curNode->lKey == value)								//если ключь найден в узле
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
	else													//продолжим поиск по узлам
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


		if ( ! eraseNode(nextNode, value))						//если удаление привело к нарушению балансировки
		{
			if ( ! distribNode(curNode, nextNode))				//пробуем перераспределим ключи
			{
				mergeNode(curNode, nextNode);					//если перераспределение не получилось сливаем ветви
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

//Функция перераспределяет узел в двух вариантах:
//1) Узел с листами - сдвигает ключи в нужной последовательности либо делает из 2-3 узла 1-2 узел.
//2) Узел с дочерними узлами:
// - если два ключа у узла, спускам один ключ вниз и цепляем к нему delNode
// - если у узла один ключ но два ключа у другого дочернего узла, то поврачива
//в случае неудачного переаспределения возвращаят false
bool tree::distribNode(node* curNode, node* delNode)
{
	if (isNodeWithLeaf(curNode))//перераспределение узл с листами
	{
		if (delNode == curNode->lNode)							//обработаем поворот узла
		{
			if (curNode->mNode->nodeSize == 2 || (curNode->nodeSize == 2 && curNode->rNode->nodeSize == 2))	//если есть ветви с 2 ключами просто сместим ключи
			{				
				delNode->lKey = curNode->lKey;
				curNode->lKey = curNode->mNode->lKey;
				delNode->nodeSize = 1;
				if (curNode->mNode->nodeSize == 2)				//обработка для двух случаев 2-3 и 1-2
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
			else if (curNode->nodeSize == 2)				//если в оставшихся листах по 1 ключу сделаем из 2-3 узла 1-2
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
			else if (curNode->nodeSize == 2)				//если в оставшихся листах по 1 ключу сделаем из 2-3 узла 1-2
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
			else if (curNode->nodeSize == 2)					//если в оставшихся листах по 1 ключу сделаем из 2-3 узла 1-2
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
	else//перераспределение узла без листов
	{
		if (delNode == curNode->lNode)
		{
			if (curNode->mNode->nodeSize == 2)					//если потмок имеет два ключа, переаспределим ключи
			{
				node* subNode = new node;						//новый дочерний узел
				curNode->lNode = subNode;
				subNode->lNode = delNode;						//подключим сразу слитую до этого ноду
				subNode->lKey = curNode->lKey;					//перераспредлим ключи
				subNode->mNode = curNode->mNode->lNode;			//перекинем дочернии ноды из соседней
				subNode->nodeSize = 1;

				curNode->lKey = curNode->mNode->lKey;			//упорядочим ключи и ноды 
				curNode->mNode->lKey = curNode->mNode->rKey;				
				curNode->mNode->nodeSize = 1;
				curNode->mNode->lNode = curNode->mNode->mNode;
				curNode->mNode->mNode = curNode->mNode->rNode;
				curNode->mNode->rNode = nullptr;
				return true;
			}
			else if(curNode->nodeSize == 2)						//если узел имеет два ключа а потмоки нет, то переделаем узел в 1-2
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
			if (curNode->lNode->nodeSize == 2)					//если левый потмок имеет два ключа, переаспределим ключи
			{
				node* subNode = new node;						//новый дочерний узел
				curNode->mNode = subNode;

				subNode->mNode = delNode;						//подключим сразу слитую до этого ноду
				subNode->lKey = curNode->lKey;					//перераспредлим ключи
				subNode->nodeSize = 1;

				subNode->lNode = curNode->lNode->rNode;			//перекинем дочернии ноды из соседней
				curNode->lNode->rNode = nullptr;

				curNode->lKey = curNode->lNode->rKey;			//упорядочим ключи и ноды 				
				curNode->lNode->nodeSize = 1;
								
				return true;
			}
			else if (curNode->nodeSize == 2 && curNode->rNode->nodeSize == 2)	//если правый потомок имеет два ключа, переаспределим ключи
			{
				node* subNode = new node;						//новый дочерний узел
				curNode->mNode = subNode;

				subNode->lNode = delNode;						//подключим сразу слитую до этого ноду
				subNode->lKey = curNode->rKey;					//перераспредлим ключи
				subNode->nodeSize = 1;

				subNode->mNode = curNode->rNode->lNode;			//перекинем дочернии ноды из соседней
				curNode->rNode->lNode = curNode->rNode->mNode;
				curNode->rNode->mNode = curNode->rNode->rNode;
				curNode->rNode->rNode = nullptr;

				curNode->rKey = curNode->rNode->lKey;			//упорядочим ключи и ноды 				
				curNode->rNode->lKey = curNode->rNode->rKey;
				curNode->rNode->nodeSize = 1;

				return true;
			}
			else if (curNode->nodeSize == 2)					//если узел имеет два ключа сделаем 1 - 2 узел
			{
				node* subNode = new node;						//новый дочерний узел
				curNode->mNode = subNode;

				subNode->lNode = delNode;						//подключим сразу слитую до этого ноду
				subNode->lKey = curNode->rKey;					//опустим ключ
				subNode->rKey = curNode->rNode->lKey;
				subNode->nodeSize = 2;
				curNode->nodeSize = 1;

				subNode->mNode = curNode->rNode->lNode;			//перекинем дочернии ноды из соседней
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
				node* subNode = new node;						//новый дочерний узел
				curNode->rNode = subNode;
				subNode->mNode = delNode;						//подключим сразу слитую до этого ноду
				subNode->lKey = curNode->rKey;					//опускаем правый ключ материнской ноды
				subNode->nodeSize = 1;

				subNode->lNode = curNode->mNode->rNode;			//перекинем дочернюю правую ноду из соседней
				curNode->mNode->rNode = nullptr;
				
				curNode->rKey = curNode->mNode->rKey;			//поднимем ключ из дочерней ноды в материнскую				
				curNode->mNode->nodeSize = 1;				
				
				return true;
			}
			else if (curNode->nodeSize == 2)					//если узел имеет два ключа а потмоки нет, то переделаем узел в 1-2
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

//Функция удаляет ключ из узла, поднимает крайний правый ключь из листа левого от ключа узла
// вызывает переаспределнее узла у котрого изьяли ключ
bool tree::returnKeyFromLeaf(node* curNode, int &value)
{
	if (isLeaf(curNode))
	{
		if (curNode->nodeSize == 1)
		{
			curNode->nodeSize = 0;									
			value = curNode->lKey;
			return false;											//если ключ в лист один веренм ложь для дальнейшего перераспределения узли или слияния
		}
		else if (curNode->nodeSize == 2)
		{
			curNode->nodeSize = 1;
			value = curNode->rKey;
			return true;											//если ключа в листе два то перераспределение не нужно
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
		
		if ( ! returnKeyFromLeaf(nextNode, value) )								//если лист после получения ключа пуст пераспределим весь узел
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

//Функция сливает соединяет два узла если не получилось удалить без потери балансировки или перераспределить ключи
//
bool tree::mergeNode(node* curNode, node* nextNode)
{
	if (nextNode->nodeSize == 0)					//обработка слияния узла с листами 
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
	else if(nextNode->nodeSize == 2)				//если перераспредлить не получилось то nextNode содержить два ключа всегда
	{
		if (curNode->lNode == nextNode)				//Склеиваем текущую ноду с дочерней
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

//****************************************Методы поиска*******************************************************
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