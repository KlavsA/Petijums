
#include <random>
#include <ctime>
#define max 400000
#define high_num max
#define low_num 1

struct Node
{
	int num;
	Node* next = NULL;
};
#pragma region "Global"
void init(int*&a)
{
	srand(time(0));
	int temp;
	for (int i = 0; i < max; i++)
	{
		temp = rand() % high_num + low_num;
		a[i] = temp;

	}
}
// Nodro�ina ka skait�i ir augo�� sec�b�
void init_asc(int*&a)
{
	srand(time(0));
	int temp;
	temp = rand() % high_num + low_num;
	a[0] = temp;
	for (int i = 1; i < max; i++)
	{
		a[i] = ++temp;
	}
}
// Nodro�ina, ka skait�i ir dilsto�� sec�b�
void init_desc(int*&a)
{
	srand(time(0));
	int temp;
	temp = rand() % high_num + low_num;
	a[0] = temp;
	for (int i = 1; i < max; i++)
	{
		a[i] = --temp;
	}
}

void init_list(Node*&a, Node* &start_a)
{

	srand(time(0));
	
	int temp;
	for (int i = 0; i < max; i++)
	{
		if (i == 0)
		{
			a = new Node;

			start_a = a;

		}
		else
		{
			a->next = new Node;
			a = a->next;

		}
		temp = rand() % high_num + low_num;

		a->num = temp;

	}
	a = start_a;


}
// Saraksta elementi ir pieaugu�� sec�b�
void init_list_asc(Node*&a, Node* &start_a)
{

	srand(time(0));
	int temp;
	temp = rand() % high_num + low_num;
	for (int i = 0; i < max; i++)
	{
		if (i == 0)
		{
			a = new Node;

			start_a = a;

		}
		else
		{
			a->next = new Node;
			a = a->next;

		}


		a->num = temp++;

	}
	a = start_a;


}
//Sarkasta elementi ir dilsto�� sec�b�
void init_list_desc(Node*&a, Node* &start_a)
{

	srand(time(0));
	int temp;
	temp = rand() % high_num + low_num;
	for (int i = 0; i < max; i++)
	{
		if (i == 0)
		{
			a = new Node;

			start_a = a;

		}
		else
		{
			a->next = new Node;
			a = a->next;

		}


		a->num = temp--;

	}
	a = start_a;


}
#pragma endregion
#pragma region "2nd implemantation"
// P�rliek elementus uz papildus atmi�as, p�c tam atpaka� uz s�kotn�jo.
void Merging_2nd(int low, int mid, int high, int* &a, int* &b) {
	int l1, l2, i;

	for (l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
		if (a[l1] <= a[l2])
		{
			b[i] = a[l1++];
		}

		else
		{
			b[i] = a[l2++];
		}

	}

	while (l1 <= mid)
	{
		b[i++] = a[l1++];
	}


	while (l2 <= high)
	{
		b[i++] = a[l2++];
	}


	for (i = low; i <= high; i++)
	{
		a[i] = b[i];
	}

}
// MergeSort, sadal��ana un apvieno�ana
void MergeSort_2nd(int low, int high, int* &a, int* b) {
	int mid;

	if (low < high) {
		mid = (low + high) / 2;
		MergeSort_2nd(low, mid, a, b);
		MergeSort_2nd(mid + 1, high, a, b);
		Merging_2nd(low, mid, high, a, b);
	}
	else {
		return;
	}
}

int main_2nd() {
	
	int * a = new int[max];
	int * b = new int[max];

	init(a);
	
	
	MergeSort_2nd(0, max - 1, a, b);
	

	delete[] a;
	delete[] b;


	return 0;
}
#pragma endregion

#pragma region "3rd implemantation"
Node* Merge_3rd(Node* a, Node* b)
{
	// Ndoro�ina, ka vienm�r ir pieejams apvienot� saraksta s�kums
	Node* result_start = NULL;
	Node* result = NULL;
	Node* result_trail = NULL;

	while (a != NULL && b != NULL)
	{
		if (a->num <= b->num)
		{
			result = a;
			a = a->next;
		}
		else
		{
			result = b;
			b = b->next;
		}
		// Lai b�tu zin�ms apvieno�anas rezult�ta s�kums
		if (result_start == NULL)
		{
			result_start = result;

		}
		// Lai saraksta mezglus savienotu vienus ar otru,
		// rezult�ts nepazustu
		if (result_trail != NULL)
		{
			result_trail->next = result;
			result_trail = result;
		}
		else
		{
			result_trail = result;
		}
		result = result->next;
	}
	// Kad ir viena sadal�t� da�a jau apskat�ta, tad atliku�o da�u pievieno kl�t
	if (a == NULL)
	{
		result = b;
	}
	else
	{
		result = a;
	}
	result_trail->next = result;

	
	return(result_start);
}


/* sadala sarakstu div�s da��s, priek��j� un aizmugur�j�
Ja elementu skaits ir nep�ra, tad atliku�ajam mezglam
j�b�t priek��j� da��.  */
void FrontBackSplit_linked_3rd_base(Node* source,
	Node** frontRef, Node** backRef)
{
	Node* fast;
	Node* slow;
	if (source == NULL || source->next == NULL)
	{
		/* ja garums <2 */
		*frontRef = source;
		*backRef = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;

		/**Nodro�ina ka tiek l�dz vidum**/
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}

		/*'slow' ir pirms vidus punkta, t�d��, taj� punkt� sadala. */
		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}
}

void MergeSort_3rd(Node** headRef)
{
	Node* head = *headRef;
	Node* a;
	Node* b;

	/* Gad�jums, ja saraksta garums 0 vai 1 */
	if ((head == NULL) || (head->next == NULL))
	{
		return;
	}

	/* Sadala sarakstu divos apak�sarakstos*/

	FrontBackSplit_linked_3rd_base(head, &a, &b);
	/* rekurs�vi sak�rto sarakstus */
	MergeSort_3rd(&a);
	MergeSort_3rd(&b);

	/* saliek sadal�tos sarakstus kop� */

	*headRef = Merge_3rd(a, b);
}




// Lai izdz�stu izveidotos saraksta elementus
void delete_list(Node*&a)
{
	Node*temp = a;
	Node*temp_back = a;
	while (temp->next != NULL)
	{
		temp_back = temp;
		temp = temp->next;
		delete temp_back;
	}
	delete temp;
}
int main_3rd() {
	
	Node * a;

	Node* start_a;


	init_list(a, start_a);

	//printf("List before MergeSort_linked_1st_base_matrixing\n");

	//for (i = 0; i < max; i++)
	//{
	//	printf("%d ", a->num);
	//	a = a->next;
	//}
	a = start_a;

	MergeSort_3rd(&a);

	/*printf("\nList after MergeSort_linked_1st_base_matrixing\n");

	for (i = 0; i < max; i++)
	{
	printf("%d ", a->num);
	a = a->next;
	}
	a = start_a;*/

	delete_list(a);



	return 0;
}
#pragma endregion


#pragma region "5th implementation"
void MergeSort_5th(int* & a, int low, int high);

// Vienk�r�a elementu apmain��ana
void swap(int*a, int i, int j) {
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
// Apvieno�ana, kur i,m ir pirm� mas�va da�as garums un j,n otr� mas�va da�as garums,
// work - ir papildus vietas(ko pa�laik nek�rto), s�kuma indeks
// K�rto attiec�gi samainot maz�ko elementu ar papildus vietas(work) pa�reiz�jo elementu
void Merge_5th(int* & a, int i, int m, int j, int n, int work) {
	while (i < m && j < n)
		swap(a, work++, a[i] < a[j] ? i++ : j++);
	while (i < m)
		swap(a, work++, i++);
	while (j < n)
		swap(a, work++, j++);
}

/*
* K�rto�anas algoritmi kas sak�rto doto mas�vu
*
*/
void MergeSort_5th_2nd(int*&a, int low, int high, int work) {
	int med;
	if (high - low > 1) {
		med = low + (high - low) / 2;
		MergeSort_5th(a, low, med);
		MergeSort_5th(a, med, high);
		Merge_5th(a, low, med, med, high, work);
	}
	else
		while (low < high)
			swap(a, low++, work++);
}

void MergeSort_5th(int*&a, int low, int high) {
	int med, n, work;
	if (high - low > 1) {
		med = low + (high - low) / 2;
		work = low + high - med;
		/* S�kuma elementi ir sak�rtoti */
		MergeSort_5th_2nd(a, low, med, work);
		// Ja v�l j�k�rto work da�� atrodam� inform�cija
		while (work - low > 2) {
			n = work;
			work = low + (n - low + 1) / 2;
			/*Iepriek��j�s work da�as s�kuma elementi ir j�apskata */
			MergeSort_5th_2nd(a, work, n, low);
			Merge_5th(a, low, low + n - work, n, high, work);
		}
		// Ja maz elementu j�apskata p�riet uz Insertion Sort
		for (n = work; n > low; --n)
			for (med = n; med < high && a[med] < a[med - 1]; ++med)
				swap(a, med, med - 1);
	}
}


int main_5th_inplace_matrix()
{
	
	int * a = new int[max];

	init(a);
	/*printf("List before MergeSort_linked_1st_base_matrixing\n");

	for (i = 0; i < max; i++)
		printf("%d ", a[i]);
*/

	MergeSort_5th(a, 0, max);

	//printf("\nList after MergeSort_linked_1st_base_matrixing\n");

	//for (i = 0; i < max; i++)
	//{
	//	printf("%d ", a[i]);
	//}


	delete[] a;


	return 0;
}
#pragma endregion

#pragma region "1st implemantation"
void Merge_1st(int*&a, int*&b, int*&c, int high, int low, int mid)
{
	// No papildus atmi�as viet�m, kas ir sak�rtotas, p�rliek elementus uz s�kotn�jo mas�vu.
	int i = 0, j = 0, low1 = low;
	for (; low1 < high; ++low1)
	{
		if (b[i] < low_num || c[j] < low_num)
		{
			break;
		}
		else if (b[i] < c[j])
		{
			a[low1] = b[i++];
		}
		else
		{
			a[low1] = c[j++];
		}
	}
	while (i < mid - low)
	{
		a[low1++] = b[i++];
	}
	while (j < high + 1 - mid)
	{
		a[low1++] = c[j++];
	}
}

void MergeSort_1st(int* &a, int high, int low)
{
	int* b;
	int* c;
	int m = (low + high) / 2;
	if (high - low > 1)
	{
		// Katrai dal��anai pie��irts jauns atmi�as apgabals
		b = new int[m - low];
		c = new int[high - m];
		memcpy(b, (void*)(a + low), sizeof(int)*(m - low));
		memcpy(c, (void*)(a + m), sizeof(int)*(high - m));
		MergeSort_1st(b, m - low, 0);
		MergeSort_1st(c, high - m, 0);
		Merge_1st(a, b, c, high - 1, low, m);
		delete[] b;
		delete[] c;
	}
	else
	{
		return;
	}

}

int main_1st()
{
	int * a = new int[max];
	init(a);
	/*printf("List before MergeSort_linked_1st_base_matrixing\n");

	for (int i = 0; i < max; i++)
		printf("%d ", a[i]);*/
	MergeSort_1st(a, max, 0);

	delete[] a;
	return 0;
}
#pragma endregion
#pragma region "4th_implemantation"
void Merge_4th(int*&a, int high, int low, int med)
{
	int i;
	int b;
	for (; low<med && med <high; low++)
	{
		if (!(a[low] < a[med]))
		{
			b = a[med];

			// Kad k�ds t�l�kais elements ir maz�ks, nek� priek�� eso�ais
			// tad p�rb�da visus elementus uz labo pusi,
			// lai var�tu ielikt maz�ko elementu attiec�g� viet�
			for (i = med; i > low; i--)
			{
				a[i] = a[i - 1];
			}
			a[low] = b;
		}
	}
}
void MergeSort_4th(int*&a, int high, int low)
{
	int m;
	if (high - low > 1)
	{
		m = (low + high) / 2;
		MergeSort_4th(a, m, low);
		MergeSort_4th(a, high, m);
		Merge_4th(a, high, low, m);
	}
	else
	{
		return;
	}
}

int main_4th_inplace_matrix()
{
	int * a = new int[max];
	init(a);


	MergeSort_4th(a, max, 0);

	delete[]a;
	return 0;

}
#pragma endregion





int main()
{
	main_1st();
	return 0;
}