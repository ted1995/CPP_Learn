class node
{
public:
	node*parent;
	node*left;
	node*right;
	int key;
	int val;
	bool color;

	node(int k,int v,node*l,node*r,node*p)
	{
		key = k;
		val = v;
		parent = p;
		left = l;
		right = r;
	}

};


class rbtree
{
public:
	node*root;
	bool red = true;
	bool black = false;

	//左旋
	void leftrotate(node*p)
	{
/*
			pf
			  \
			   p(待旋转结点)
			  / \
			 pl  pr
				 / \
				rl	 rr
*/

		if (p != nullptr)
		{
			node*pf = p->parent;
			node*pr = p->right;
			node*rl = p->right->left;

			//先将rl连向p
			p->right = rl;
			if (rl != nullptr)
			{
				//当前结点不为空，才会有父节点
				rl->parent = p;
			}

			//将pr连向p
			//pf是空说明p是根结点，此时将根结点换成pr，pr的父节点变为空
			if (pf == nullptr)
			{
				root = pr;
				pr->parent = nullptr;
			}
			//pf非空说明p不是根结点，有自己的父节点，再判断p是pf的左节点还是右节点，以此来确定pr的位置
			else if(pf->left==p)
			{
				pf->left = pr;
			}
			else if (pf->right == p)
			{
				pf->right = pr;
			}

			//将p连向pr
			p->parent = pr;
			pr->left = p;
		}
	}

	//右旋
	void rightrotate(node*p)
	{
		/*
				pf
				/
			   p(待旋转结点)
			  / \
			 pl  pr
			/ \
		  rl  rr
		*/

		if (p != nullptr)
		{
			node*pf = p->parent;
			node*pl = p->right;
			node*rr = p->right->left;

			//先将rr连向p
			p->left = rr;
			if (rr != nullptr)
			{
				//当前结点不为空，才会有父节点
				rr->parent = p;
			}

			//将pl连向p
			//pf是空说明p是根结点，此时将根结点换成pl，pl的父节点变为空
			if (pf == nullptr)
			{
				root = pl;
				//根结点的父节点为空
				pl->parent = nullptr;
			}
			//pf非空说明p不是根结点，有自己的父节点，再判断p是pf的左节点还是右节点，以此来确定pl的位置
			else if (pf->left == p)
			{
				pf->left = pl;
			}
			else if (pf->right == p)
			{
				pf->right = pl;
			}

			//将p连向pr
			p->parent = pl;
			pl->left = p;
		}
	}



	//插入值
	void put(int k, int v)
	{
		//插入的是根结点
		node* t = this->root;
		if (t == nullptr)
		{
			this->root = new node(k, v, nullptr,nullptr,nullptr);
			return;
		}
		//非根节点，查找插入位置
		node*p;
		while (t != nullptr)
		{
			p = t;
			if (t->key > k)
			{
				t = t->left;
			}
			else if (t->key < k)
			{
				t = t->right;
			}
			//找到相同键值，直接替换val然后退出。
			else
			{
				t->val = v;
				return;
			}
		}
		//跳出循环说明找到了一个空节点插入位置
		t = new node(k, v, nullptr, nullptr, p);
		if (t->key < p->key)
		{
			p->left = t;
		}
		else
		{
			p->right = t;
		}

		//旋转或者变色
		fix(t);
	}

	//调整
	void fix(node*x)
	{
		//父节点是黑色，那么直接插入就行，结点颜色调整为红色，即可,不需要做旋转和变色
		x->color = red;

		//父节点是红色，需要根据情况进行调整
		while (x != root && x->parent->color == red)
		{
			node*gp = x->parent->parent;
			node*p = x->parent;
			//1. 4结点加入新元素这种（有2-3-4树而来，2结点有一个元素，但可以生成两个子树，所以叫2结点）
			if ((gp->right != nullptr && gp->right->color == red) || (gp->left != nullptr && gp->left->color == red))
			{
				/*
						(gp)B
						   / \
					   (p)R   R
						 /
						R(x)
									=》变色
						(gp)R
						   / \
					   (p)B   B
						 /
						R(x)
				*/
				//只需要改变颜色，不需要旋转
				gp->left->color = black;
				gp->right->color = black;
				gp->color = red;
				//因为这种方式改变了当前子树的根结点的颜色，可能会造成与上面的结点颜色冲突，因此以爷爷结点再次执行上面的判断
				x = gp;

			}
			//2. 3结点加入新元素
			else if (gp->right == nullptr)
			{
				if (x = p->left)
				{
					/*
								(GP)B
								   /
							   (P)R
								 /
							 (X)R
										=》变色+旋转（以gp为支点）
							   (P)B
								 / \
							 (X)R   R(GP)
				*/
					p->color = black;
					gp->color = red;
					//以插入节点的爷爷结点为旋转结点
					rightrotate(gp);
					//无需循环判断，直接跳出循环
					break;
				}
				if (x = p->right)
				{
					/*
								(GP)B
								   /
							   (P)R
								   \
								    R(X)
										=》左旋（以p为支点）
								(GP)B
								   /
							   (X)R
								 / 
							 (P)R  
				    */
					leftrotate(p);
					//变成左样式
					x->color = black;
					gp->color = red;
					//以插入节点的爷爷结点为旋转结点
					rightrotate(gp);
					//无需循环判断，直接跳出循环
					break;
				}
			
				
			}
			//3. 3结点加入新元素
			else if (gp->left == nullptr)
			{
				if (x = p->right)
				{
					/*
								(GP)B
									 \
								   (P)R
									   \
										R(X)
				    */
					gp->right->color = black;
					gp->color = red;
					leftrotate(gp);
					//无需循环判断，直接跳出循环
					break;
				}
				if (x = p->left)
				{
					/*
								(GP)B
									 \
								   (P)R
									 /
									R(X)
					*/
					//变成右样式
					rightrotate(p);
					x->color = black;
					gp->color = red;
					//以插入节点的爷爷结点为旋转结点
					leftrotate(gp);
					//无需循环判断，直接跳出循环
					break;
				}
				
			}
		}
		//结束循环，要么遍历到根结点，要么是父节点是黑色，不需要继续遍历
		//确保根结点为黑色，因为有的循环到根结点，会改变很结点的颜色
		root->color = black;
	}

	//获取前驱结点
	node* getfront(node *n)
	{
		if (n == nullptr)
		{
			return nullptr;
		}
		else if (n->left != nullptr)
		{
			//沿左子树一直往右走
			node *temp = n->left;
			while (temp->right != nullptr)
			{
				temp = temp->right;
			}
			return temp;
		}
		else
		{
			//特殊情况,无左结点，但是有前驱结点
			node*p = n->parent;
			node*c = n;
			while (p != nullptr&&c == p->left)
			{
				c = p;
				p = p->parent;
			}
			return p;
		}
	}


	//获取后继结点
	node* getback(node *n)
	{
		if (n == nullptr)
		{
			return nullptr;
		}
		else if (n->right != nullptr)
		{
			//沿右子树一直往左走
			node *temp = n->right;
			while (temp->left != nullptr)
			{
				temp = temp->left;
			}
			return temp;
		}
		else
		{
			//特殊情况,无右结点，但是有后继结点
			node*p = n->parent;
			node*c = n;
			while (p != nullptr&&c == p->right)
			{
				c = p;
				p = p->parent;
			}
			return p;
		}
	}

	
	//删除：找到后继或者前驱结点，值替换，然后再删除后继或者前驱结点，简单省事
	void remove(int k)
	{
		//找到k值结点
		node*temp = getnode(k);
		if (temp == nullptr)
		{
			return;
		}
		del(temp);

	}


void del(node* n)
{
	/*
		删除：
		1.删除结点有两个子节点，找到前驱或后继结点，替代删除
		2.删除结点有一个子节点，用子节点替代
		3.删除结点是叶子结点，直接删除
	
	*/

	//1.原要删除结点有两个子节点
	if (n->left != nullptr&&n->right != nullptr)
	{
		node* back = getback(n);
		n->key = back->key;
		n->val = back->val;
		n = back;
	}
	/*
		此时原要删除结点不用删除，新的要删除的结点为后继结点，且此节点两种情况：有一个子节点或者无子节点

		此时1两个子节点的情况变成了2一个子节点或3无子节点的删除情况，直接用删除2、3的方法删除即可。
	*/
		
	//替代结点
	node* replace = n->right;
	//替代结点不为空
	//2.即原删除结点有一个子节点或者后继结点有一个子节点
	if (replace != nullptr)
	{
		//先删除结点再调整
		//且后继结点是根结点
		if (n->parent == nullptr)
		{
				/*
					n(root)
					\
					replace
				*/
			//替代结点成为根结点
			root->left->parent = replace;
			replace->left = root->left;
			replace->color = red;
			delete root;
			root = replace;
			return;
		}
		//后继结点不是根结点
		else if(n==n->parent->left)
		{
			/*
					parent
					/
					n
					\
					replace
				*/
			n->parent->left = replace;
			replace->parent = n->parent;
		}
		else if (n == n->parent->right)
		{
			/*
					parent
					\
						n
						\
						replace
				*/
			n->parent->right = replace;
			replace->parent = n->parent;
		}
		//如果删掉的是黑色结点，需要调整
		if (n->color==black)
		{
			//先释放结点内存
			delete n;
			n = nullptr;
			//以替代结点为支点调整
			fix(replace);
		}
				
	}
	//替代结点为空
	//3.原删除结点没有子节点或者后继结点没有子节点
	else
	{
		//后继结点为根结点
		if (n->parent == nullptr)
		{
			//此时红黑树无元素
			root = nullptr;
		}
		//后继结点不为根结点
		//先调整再删除结点
		else
		{
			//调整
			if (n->color == black)
			{
				return;
			}
			//删除
			if (n == n->parent->left)
			{
				/*
						parent
						\
							n
					*/
				n->parent->left = nullptr;
				delete n;
				n = nullptr;
			}
			else if (n == n->parent->right)
			{
				/*
							parent
						/
						n
					*/
				n->parent->right = nullptr;
				delete n;
				n = nullptr;
			}
		}
	}
}


	//查找
	node* getnode(int k)
	{
		node*temp = root;
		while (temp != nullptr)
		{
			if (temp->key < k)
			{
				temp = temp->right;
			}
			else if (temp->key > k)
			{
				temp = temp->left;
			}
			else
			{
				return temp;
			}
		}
		return temp;
	}
};

