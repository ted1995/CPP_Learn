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

	//����
	void leftrotate(node*p)
	{
/*
			pf
			  \
			   p(����ת���)
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

			//�Ƚ�rl����p
			p->right = rl;
			if (rl != nullptr)
			{
				//��ǰ��㲻Ϊ�գ��Ż��и��ڵ�
				rl->parent = p;
			}

			//��pr����p
			//pf�ǿ�˵��p�Ǹ���㣬��ʱ������㻻��pr��pr�ĸ��ڵ��Ϊ��
			if (pf == nullptr)
			{
				root = pr;
				pr->parent = nullptr;
			}
			//pf�ǿ�˵��p���Ǹ���㣬���Լ��ĸ��ڵ㣬���ж�p��pf����ڵ㻹���ҽڵ㣬�Դ���ȷ��pr��λ��
			else if(pf->left==p)
			{
				pf->left = pr;
			}
			else if (pf->right == p)
			{
				pf->right = pr;
			}

			//��p����pr
			p->parent = pr;
			pr->left = p;
		}
	}

	//����
	void rightrotate(node*p)
	{
		/*
				pf
				/
			   p(����ת���)
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

			//�Ƚ�rr����p
			p->left = rr;
			if (rr != nullptr)
			{
				//��ǰ��㲻Ϊ�գ��Ż��и��ڵ�
				rr->parent = p;
			}

			//��pl����p
			//pf�ǿ�˵��p�Ǹ���㣬��ʱ������㻻��pl��pl�ĸ��ڵ��Ϊ��
			if (pf == nullptr)
			{
				root = pl;
				//�����ĸ��ڵ�Ϊ��
				pl->parent = nullptr;
			}
			//pf�ǿ�˵��p���Ǹ���㣬���Լ��ĸ��ڵ㣬���ж�p��pf����ڵ㻹���ҽڵ㣬�Դ���ȷ��pl��λ��
			else if (pf->left == p)
			{
				pf->left = pl;
			}
			else if (pf->right == p)
			{
				pf->right = pl;
			}

			//��p����pr
			p->parent = pl;
			pl->left = p;
		}
	}



	//����ֵ
	void put(int k, int v)
	{
		//������Ǹ����
		node* t = this->root;
		if (t == nullptr)
		{
			this->root = new node(k, v, nullptr,nullptr,nullptr);
			return;
		}
		//�Ǹ��ڵ㣬���Ҳ���λ��
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
			//�ҵ���ͬ��ֵ��ֱ���滻valȻ���˳���
			else
			{
				t->val = v;
				return;
			}
		}
		//����ѭ��˵���ҵ���һ���սڵ����λ��
		t = new node(k, v, nullptr, nullptr, p);
		if (t->key < p->key)
		{
			p->left = t;
		}
		else
		{
			p->right = t;
		}

		//��ת���߱�ɫ
		fix(t);
	}

	//����
	void fix(node*x)
	{
		//���ڵ��Ǻ�ɫ����ôֱ�Ӳ�����У������ɫ����Ϊ��ɫ������,����Ҫ����ת�ͱ�ɫ
		x->color = red;

		//���ڵ��Ǻ�ɫ����Ҫ����������е���
		while (x != root && x->parent->color == red)
		{
			node*gp = x->parent->parent;
			node*p = x->parent;
			//1. 4��������Ԫ�����֣���2-3-4��������2�����һ��Ԫ�أ������������������������Խ�2��㣩
			if ((gp->right != nullptr && gp->right->color == red) || (gp->left != nullptr && gp->left->color == red))
			{
				/*
						(gp)B
						   / \
					   (p)R   R
						 /
						R(x)
									=����ɫ
						(gp)R
						   / \
					   (p)B   B
						 /
						R(x)
				*/
				//ֻ��Ҫ�ı���ɫ������Ҫ��ת
				gp->left->color = black;
				gp->right->color = black;
				gp->color = red;
				//��Ϊ���ַ�ʽ�ı��˵�ǰ�����ĸ�������ɫ�����ܻ����������Ľ����ɫ��ͻ�������үү����ٴ�ִ��������ж�
				x = gp;

			}
			//2. 3��������Ԫ��
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
										=����ɫ+��ת����gpΪ֧�㣩
							   (P)B
								 / \
							 (X)R   R(GP)
				*/
					p->color = black;
					gp->color = red;
					//�Բ���ڵ��үү���Ϊ��ת���
					rightrotate(gp);
					//����ѭ���жϣ�ֱ������ѭ��
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
										=����������pΪ֧�㣩
								(GP)B
								   /
							   (X)R
								 / 
							 (P)R  
				    */
					leftrotate(p);
					//�������ʽ
					x->color = black;
					gp->color = red;
					//�Բ���ڵ��үү���Ϊ��ת���
					rightrotate(gp);
					//����ѭ���жϣ�ֱ������ѭ��
					break;
				}
			
				
			}
			//3. 3��������Ԫ��
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
					//����ѭ���жϣ�ֱ������ѭ��
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
					//�������ʽ
					rightrotate(p);
					x->color = black;
					gp->color = red;
					//�Բ���ڵ��үү���Ϊ��ת���
					leftrotate(gp);
					//����ѭ���жϣ�ֱ������ѭ��
					break;
				}
				
			}
		}
		//����ѭ����Ҫô����������㣬Ҫô�Ǹ��ڵ��Ǻ�ɫ������Ҫ��������
		//ȷ�������Ϊ��ɫ����Ϊ�е�ѭ��������㣬��ı�ܽ�����ɫ
		root->color = black;
	}

	//��ȡǰ�����
	node* getfront(node *n)
	{
		if (n == nullptr)
		{
			return nullptr;
		}
		else if (n->left != nullptr)
		{
			//��������һֱ������
			node *temp = n->left;
			while (temp->right != nullptr)
			{
				temp = temp->right;
			}
			return temp;
		}
		else
		{
			//�������,�����㣬������ǰ�����
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


	//��ȡ��̽��
	node* getback(node *n)
	{
		if (n == nullptr)
		{
			return nullptr;
		}
		else if (n->right != nullptr)
		{
			//��������һֱ������
			node *temp = n->right;
			while (temp->left != nullptr)
			{
				temp = temp->left;
			}
			return temp;
		}
		else
		{
			//�������,���ҽ�㣬�����к�̽��
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

	
	//ɾ�����ҵ���̻���ǰ����㣬ֵ�滻��Ȼ����ɾ����̻���ǰ����㣬��ʡ��
	void remove(int k)
	{
		//�ҵ�kֵ���
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
		ɾ����
		1.ɾ������������ӽڵ㣬�ҵ�ǰ�����̽�㣬���ɾ��
		2.ɾ�������һ���ӽڵ㣬���ӽڵ����
		3.ɾ�������Ҷ�ӽ�㣬ֱ��ɾ��
	
	*/

	//1.ԭҪɾ������������ӽڵ�
	if (n->left != nullptr&&n->right != nullptr)
	{
		node* back = getback(n);
		n->key = back->key;
		n->val = back->val;
		n = back;
	}
	/*
		��ʱԭҪɾ����㲻��ɾ�����µ�Ҫɾ���Ľ��Ϊ��̽�㣬�Ҵ˽ڵ������������һ���ӽڵ�������ӽڵ�

		��ʱ1�����ӽڵ����������2һ���ӽڵ��3���ӽڵ��ɾ�������ֱ����ɾ��2��3�ķ���ɾ�����ɡ�
	*/
		
	//������
	node* replace = n->right;
	//�����㲻Ϊ��
	//2.��ԭɾ�������һ���ӽڵ���ߺ�̽����һ���ӽڵ�
	if (replace != nullptr)
	{
		//��ɾ������ٵ���
		//�Һ�̽���Ǹ����
		if (n->parent == nullptr)
		{
				/*
					n(root)
					\
					replace
				*/
			//�������Ϊ�����
			root->left->parent = replace;
			replace->left = root->left;
			replace->color = red;
			delete root;
			root = replace;
			return;
		}
		//��̽�㲻�Ǹ����
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
		//���ɾ�����Ǻ�ɫ��㣬��Ҫ����
		if (n->color==black)
		{
			//���ͷŽ���ڴ�
			delete n;
			n = nullptr;
			//��������Ϊ֧�����
			fix(replace);
		}
				
	}
	//������Ϊ��
	//3.ԭɾ�����û���ӽڵ���ߺ�̽��û���ӽڵ�
	else
	{
		//��̽��Ϊ�����
		if (n->parent == nullptr)
		{
			//��ʱ�������Ԫ��
			root = nullptr;
		}
		//��̽�㲻Ϊ�����
		//�ȵ�����ɾ�����
		else
		{
			//����
			if (n->color == black)
			{
				return;
			}
			//ɾ��
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


	//����
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

