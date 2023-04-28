#ifndef PAS_01_H
#define PAS_01_H

struct daftarbuah {		//struktur linked list untuk buah yang dijual
	int id;
	char nama[20];
	float jumlah;
	int harga;
	int ddin;
	int mmin;
	int yyin;
	struct daftarbuah *next;
};

struct daftarpembeli {		//struktur linked list untuk riwayat pembeli
	int id;
	char namabuah[20];
	int ddbuy;
	int mmbuy;
	int yybuy;
	float jumlah;
	float hargatotal;
	struct daftarpembeli *next;
};

struct historypembeli {		//struktur linked list untuk statistik histogram
	char namabuah[20];
	float jumlah;
	float hargatotal;
	struct historypembeli *next;
};

struct dataadmin {			//struktur linkedlist untuk admin yang bisa masuk
	char id[20];
	char password[20];
	struct dataadmin *next;
};

typedef struct daftarbuah listbuah;
typedef struct daftarpembeli listpembeli;
typedef struct historypembeli listhistogram;
typedef struct dataadmin listadmin;


listbuah *headbuah = NULL;				//header linked list list buah
listpembeli *headpembeli = NULL;		//header linked list list pembeli
listhistogram *headhistogram = NULL;	//header linked list list histogram
listadmin *headadmin = NULL;

void createlistadmin(char id[20], char password[20]){	//fungsi untuk memmbuat linked list admin
	listadmin *node, *temp;
	node = (listadmin*)malloc(sizeof(listadmin));	//buat memory untuk menyimpan linked list listbuah di pointer node
	strcpy(node->id, id);
	strcpy(node->password, password);		
	
	if(headadmin == NULL){			//jika header kosong, arahkan ke node
		headadmin = node;
		headadmin->next = NULL;
		return;
	}

	temp = headadmin;

	while(temp->next != NULL){		//jika header sudah ada masukkan ke alamat berikutnya
		temp = temp->next;
	}

	temp->next = node;
	node->next = NULL;
}

void readpass(char *password){		//fungsi untuk membaca passaword yang diketik ketika masuk menu admin
	int key = 0, index = 0;
 
    do {
        key = getch(); 				// Simpan karakter yang ditekan ke dalam variabel key 
 
        switch (key) {
            case 0:
            	
            case 224:				//Jika enter, keluar
                getch();
                break;
	
            case '\b':				//Jika backspace, kurangi 1
                if (index > 0) {
                    index = index - 1; 
                    password[index] = 0; 
 
                    printf("\b \b"); 	//Kursor mundur 1 space
                }
 
                break;
                
            default:					//jika yang diketik alfanumerik, tambah ke key
                if (key > 31 && key < 127) {
                    password[index] = key; 
                    index = index + 1;
 
                    printf("*");		//print *, bukan karakternya
                }
        }
    } while (key != 13); 				// Menambahkan NUL di akhir temp yang menandakan akhir dari sebuah string				
    password[index] = '\0';
}

void masukadmin(){						//fungsi untuk masuk menu admin
	int restart = 0;
	char id[20];
	char password[20];
	int input = 0;
	
	createlistadmin("Fathurrahman", "fathur843");		// id & password buat Fathur
	createlistadmin("Leonard", "leon586");				// id & password buat leon
	
	while(restart != 1){
		system("cls");
		fflush(stdin);
		printf("============================================================\n");	//Main Menu Program
	    printf("||              SISTEM ADMINISTRASI TOKO BUAH             ||\n");
		printf("============================================================\n");
		printf("\nMasukkan data admin");
		printf("\n\nID\t\t: ");
		scanf("%s", &id);
		printf("Password\t: ");
		readpass(password);
		
		listadmin *temp = headadmin;
		
		while(temp != NULL){														//traverse linkedlist admin
			if(strcmp(id, temp->id) == 0 && strcmp(password, temp->password) == 0){	//Cek jika id & pasword sama
				restart = 1;
				input = 1;
				break;
			}
			temp= temp->next;
		}
		
		if(input == 1){
			printf("\n\nInput Berhasil...");
			getch();
		}
		else{
			printf("\n\nID/Password yang anda masukkan salah!");
			free(temp);
			getch();
		}
		
	}
}

void createlistbuah(char namabuah[], int idbuah, float jumlahbuah, int hargabuah, int ddin, int mmin, int yyin){		// fungsi untuk membuat linked list buah yang dijual
	listbuah *node, *temp;
	node = (listbuah*)malloc(sizeof(listbuah));	//buat memory untuk menyimpan linked list listbuah di pointer node
	strcpy(node->nama, namabuah);		//copy data namabuah, idbuah, jumlahbuah, hargabuah, day, month, dan year buah ke linked list listbuah
	node->id = idbuah;
	node->jumlah = jumlahbuah;
	node->harga = hargabuah;
	node->ddin = ddin;
	node->mmin = mmin;
	node->yyin = yyin;
	
	if(headbuah == NULL){			//jika header kosong, arahkan ke node
		headbuah = node;
		headbuah->next = NULL;
		return;
	}

	temp = headbuah;

	while(temp->next != NULL){		//jika header sudah ada masukkan ke alamat berikutnya
		temp = temp->next;
	}

	temp->next = node;
	node->next = NULL;
}

void header(){			//header untuk print listbuah
	printf("==================================================================================================\n");
	printf("|                                          List Buah                                             |");
	printf("\n==================================================================================================\n");
	printf("| %-5s | %-25s | %-15s | %-7s | %-7s | %-20s |\n",  "ID", "Nama Buah", "Tanggal Masuk", "Jumlah", "Harga", "Rincian");
	printf("================================================================================================\n");
}

void tabel(listbuah *temp){			//tabel listbuah	
	printf("| %-5d | %-25s | %4d/%d/%-7d | %-7.2f | %-7d |", temp->id, temp->nama, temp->ddin, temp->mmin, temp->yyin, temp->jumlah, temp->harga);
	if(strstr(temp->nama, "Pisang") != NULL){			//Jika Pisang, maka /sisir
		printf(" %-20s |\n", "/Sisir (0.9-1,2 Kg)");
	}
	else if(strstr(temp->nama, "Semangka") != NULL ){	//Jika semangka, maka/buah
		printf(" %-20s |\n","/Buah (3,2-4,6 Kg)");
	}
	else if(strstr(temp->nama, "Nanas") != NULL ){		//Jika Nanas, maka /buah
		printf(" %-20s |\n","/Buah (0,4-1 Kg)");
	}
	else if(strstr(temp->nama, "Melon") != NULL ){		//Jika Melon, maka buah
		printf(" %-20s |\n","/Buah (1,6-2,4 Kg)");
	}
	else{												//Selain itu. maka /kg
		printf(" %-20s |\n", "/Kg");
	}
}

void printlistbuah(){		//print linked list buah dalam bentuk tabel
	listbuah *temp;
	temp = headbuah;

	if(temp == NULL){
		printf("Linked list is empty\n");
	}

	while(temp->next != NULL){
		tabel(temp);
		temp = temp->next;
	}
	tabel(temp);
}

void printlistpembeli(){		//print linked list pembeli dalam bentuk tabel
	listpembeli *temp;
	temp = headpembeli;
	
	if(temp == NULL){
		printf("Linked list is Pembeli empty\n");
		return;
	}
	
	printf("========================================================================================================\n");
	printf("|                                              Riwayat Penjualan                                       |");
	printf("\n========================================================================================================\n");
	printf("| %-10s | %-20s | %-20s | %-7s | %-20s | %-7s  |\n",  "ID Pembeli", "Nama Buah", "Tanggal Penjualan", "Jumlah", "Rincian", "Total");
	printf("========================================================================================================\n");
	
	while(temp->next != NULL){
		printf("| %-10d | %-20s | %7d/%d/%-9d | %-7.2f |", temp->id, temp->namabuah, temp->ddbuy, temp->mmbuy, temp->yybuy, temp->jumlah);
		if(strstr(temp->namabuah, "Pisang") != NULL){			//Jika Pisang, maka /sisir
			printf(" %-20s | %-7.2f |\n", "/Sisir (0.9-1,2 Kg)", temp->hargatotal);
		}
		else if(strstr(temp->namabuah, "Semangka") != NULL ){	//Jika semangka, maka /buah
			printf(" %-20s | %-7.2f |\n","/Buah (3,2-4,6 Kg)", temp->hargatotal);
		}
		else if(strstr(temp->namabuah, "Nanas") != NULL ){	//Jika Nanas, maka /buah
			printf(" %-20s | %-7.2f |\n","/Buah (0,4-1 Kg)", temp->hargatotal);
		}
		else if(strstr(temp->namabuah, "Melon") != NULL ){	//Jika Melon, maka /buah
			printf(" %-20s | %-7.2f |\n","/Buah (1,6-2,4 Kg)", temp->hargatotal);
		}
		else{													//Selain itu. maka /kg
			printf(" %-20s | %-7.2f |\n", "/Kg", temp->hargatotal);
		}
		temp = temp->next;
	}
	printf("| %-10d | %-20s | %7d/%d/%-9d | %-7.2f |", temp->id, temp->namabuah, temp->ddbuy, temp->mmbuy, temp->yybuy, temp->jumlah);
	if(strstr(temp->namabuah, "Pisang") != NULL){			//Jika Pisang, maka /sisir
		printf(" %-20s | %-7.2f |\n", "/Sisir (0.9-1,2 Kg)", temp->hargatotal);
	}
	else if(strstr(temp->namabuah, "Semangka") != NULL ){	//Jika semangka, maka /buah
		printf(" %-20s | %-7.2f |\n","/Buah (3,2-4,6 Kg)", temp->hargatotal);
	}
	else if(strstr(temp->namabuah, "Nanas") != NULL ){	//Jika Nanas, maka /buah
		printf(" %-20s | %-7.2f |\n","/Buah (0,4-1 Kg)", temp->hargatotal);
	}
	else if(strstr(temp->namabuah, "Melon") != NULL ){	//Jika Melon, maka /buah
		printf(" %-20s | %-7.2f |\n","/Buah (1,6-2,4 Kg)", temp->hargatotal);
	}
	else{													//Selain itu. maka /kg
		printf(" %-20s | %-7.2f |\n", "/Kg", temp->hargatotal);
	}
	printf("========================================================================================================\n");
}

void printlisthistogram(){		//print linked list histogram dalam bentuk histogram
	int i = 0;
	listhistogram *temp1, *temp2;
	temp1 = headhistogram;

	if(temp1 == NULL || temp2 == NULL){
		printf("Linked list Histogram is empty\n");
		return;
	}

	printf("\n\n=============================================================================================================\n");
	printf("|                                            Hasil Penjualan  (Harga)                                       |");
	printf("\n=============================================================================================================\n\n");	
				
	while(temp1->next != NULL){							//akan traverse linked list histogram
		printf(" %-25s |", temp1->namabuah);
		for(i = temp1->hargatotal; i >= 0 ; i -= 2500){	//setiap # menandakan Rp. 2500
			printf("#");
		}
		printf("    Rp.%-7.0f\n", temp1->hargatotal);
		temp1 = temp1->next;	
	}
	printf(" %-25s |", temp1->namabuah);
	for(i = temp1->hargatotal; i >= 0 ; i -= 2500){
		printf("#");
	}
	printf("    Rp.%-7.0f\n", temp1->hargatotal);
	
	printf("\n=============================================================================================================\n");
	printf("Keterangan: Setiap '#' menunjukkan Rp2500\n");
	printf("\n\n=============================================================================================================\n");
	printf("|                                            Hasil Penjualan  (Jumlah)                                      |");
	printf("\n=============================================================================================================\n\n");	
	temp2 = headhistogram;			
	while(temp2->next != NULL){						//akan traverse linked list histogram
		printf(" %-25s |", temp2->namabuah);
		for(i = temp2->jumlah; i > 0 ; i -= 1){	//setiap # menandakan 1 item
			printf("#");
		}
		printf("    %-2.0f", temp2->jumlah);
		
		if(strstr(temp2->namabuah, "Pisang") != NULL){			//Jika Pisang, maka /sisir
			printf("%-20s\n", "/Sisir (0.9-1,2 Kg)");
		}
		else if(strstr(temp2->namabuah, "Semangka") != NULL ){	//Jika semangka, maka /buah
			printf("%-20s\n","/Buah (3,2-4,6 Kg)");
		}
		else if(strstr(temp2->namabuah, "Nanas") != NULL ){	//Jika Nanas, maka /buah
			printf("%-20s\n","/Buah (0,4-1 Kg)");
		}
		else if(strstr(temp2->namabuah, "Melon") != NULL ){	//Jika Melon, maka /buah
			printf("%-20s\n","/Buah (1,6-2,4 Kg)");
		}
		else{
			printf("%-20s\n", "/Kg");							//Selain itu. maka /kg
		}
		
		temp2 = temp2->next;
	}
	printf(" %-25s |", temp2->namabuah);
	for(i = temp2->jumlah; i > 0 ; i -= 1){
		printf("#");
	}
	printf("    %-2.0f", temp2->jumlah);
	
	if(strstr(temp2->namabuah, "Pisang") != NULL){			//Jika Pisang, maka /sisir
		printf("%-20s\n", "/Sisir (0.9-1,2 Kg)");
	}
	else if(strstr(temp2->namabuah, "Semangka") != NULL ){	//Jika semangka, maka /buah
		printf("%-20s\n","/Buah (3,2-4,6 Kg)");
	}
	else if(strstr(temp2->namabuah, "Nanas") != NULL ){	//Jika Nanas, maka /buah
		printf("%-20s\n","/Buah (0,4-1 Kg)");
	}
	else if(strstr(temp2->namabuah, "Melon") != NULL ){	//Jika Melon, maka /buah
		printf("%-20s\n","/Buah (1,6-2,4 Kg)");
	}
	else{
		printf("%-20s\n", "/Kg");							//Selain itu. maka /kg
	}
	
	printf("\n===============================================================================================================\n");
	printf("Keterangan: Setiap '#' menunjukkan 1 item\n");
}

void updatebuahlama(int id, char buffer[]){			//Melakukan restock pada list buah yang sudah ada
	const char s[2] = "/";
	char *token;
	int opsi, anchor = 0;
	float jumlah;
	int dataddin, datammin, datayyin;
	listbuah *temp;
	temp = headbuah;
	
	token =strtok(buffer, s);
	
	printf("================================================\n");
	while(temp != NULL){											//traverse linked list listbuah
		if(id == temp->id){											//jika id ditermukan
			printf("Nama Buah: %s", temp->nama);					//print nama
			printf("\nTambah Jumlah Baru: ");						//tambahkan jumlah restock
			scanf("%f", &jumlah);   
			temp->jumlah += jumlah;
			printf("\nJumlah Sekarang: %.2f", temp->jumlah);
			printf("\nIngin ganti harga? (1=No, 2=Yes): ");			//ganti harga atau tidak(tergantung musim)
			scanf("%d", &opsi);
			if(opsi == 2){
				printf("Harga Baru: ");
				scanf("%d", &(temp->harga));
			}
			
		    while(token != NULL){									//update tanggal restock
				
				if(anchor == 0){
					dataddin = atoi(token);
				}
				else if(anchor == 1){
					datammin = atoi(token);
				}
				else{
					datayyin = atoi(token);
				}
				token = strtok(NULL,s);
				anchor++;
			}
		    return;
		}
		temp = temp->next;
	}
}

void updatebuahbaru(char buffer[]){									//menembahkan buah yang baru pada daftar list buah
	const char s[2] = "/";
	char *token;
	int id, harga, anchor = 0;
	float jumlah;
	char nama[20], tanggalmasuk[20];
	int dataddin, datammin, datayyin;
	listbuah *temp;
	temp = headbuah;
	token = strtok(buffer, s);
	
	printf("================================================\n");
	while(temp != NULL){										//traverse linked list listbuah
		printf("Input ID baru: ");								//input id, nama, jumlah, harga baru
		scanf("%d", &id);
		printf("Input nama buah baru: ");
		scanf("%d", &temp);
	    scanf("%[^\n]", &nama);
		printf("Input jumlah baru: ");
		scanf("%f", &jumlah);
		printf("Input harga baru: ");
		scanf("%d", &harga);
		while(token != NULL){									//update tanggal restock

			if(anchor == 0){
				dataddin = atoi(token);
			}
			else if(anchor == 1){
				datammin = atoi(token);
			}
			else{
				datayyin = atoi(token);
			}
			token = strtok(NULL,s);
			anchor++;
		}
		createlistbuah(nama, id, jumlah, harga, dataddin, datammin, datayyin);
		return;
	}
	temp = temp->next;
}

void deletebuah(int id){								//mendelete buah berdasarkan id yang diinginkan
	listbuah *temp, *prev;
	temp = headbuah;
	
    if (temp != NULL && temp->id == id) {				//jika awal headnya adalah id yang dicari
        headbuah = temp->next;							//ubah ke alamat di dalamny
        free(temp);										//hilangkan alamat head lama
        return;
    }
    while (temp != NULL && temp->id != id) {			//melakukan traversing, keep track jika ada id yang sama
        prev = temp;								
        temp = temp->next;
    }
    prev->next = temp->next;							//unlink nodenya dari linked list
    free(temp);											//hilangkan alamatnya
}

void swap(listbuah *ptr1, listbuah *ptr2){				//fungsi swap untuk sorting
	int tempint;
	float tempfloat;
	char tempchar[20];									//swap id, namabuah, jumlah, harga, day, month, year buah
	
	tempint = ptr1->id;
	ptr1->id = ptr2->id;
	ptr2->id = tempint;
	
	strcpy(tempchar, ptr1->nama);
	strcpy(ptr1->nama, ptr2->nama);
	strcpy(ptr2->nama, tempchar);
	
	tempfloat = ptr1->jumlah;
	ptr1->jumlah = ptr2->jumlah;
	ptr2->jumlah = tempfloat;
	
	tempint = ptr1->harga;
	ptr1->harga = ptr2->harga;
	ptr2->harga = tempint;
	
	tempint = ptr1->ddin;
	ptr1->ddin = ptr2->ddin;
	ptr2->ddin = tempint;
	
	tempint = ptr1->mmin;
	ptr1->mmin = ptr2->mmin;
	ptr2->mmin = tempint;
	
	tempint = ptr1->yyin;
	ptr1->yyin = ptr2->yyin;
	ptr2->yyin = tempint;
}

void sortnamabuah(int sorttype){								//fungsi bubble sort berdasarkan nama buah
	listbuah *pembanding, *dibanding;
	pembanding = headbuah;
	dibanding = NULL;
	
	if(sorttype == 1){											//jika 1, maka Ascending 
		if(pembanding == NULL){
			return;
		}
		else{
			while(pembanding != NULL){
				dibanding = pembanding->next;
				
				while(dibanding != NULL){
					if(strcmp(pembanding->nama, dibanding->nama) > 0){	//jika nama sebelum > sesudah, lakukan swap
						swap(pembanding, dibanding);
					}
					dibanding = dibanding->next;
				}
				pembanding=pembanding->next;
			}
		}
	}
	else if(sorttype == 2){									//jika 2, maka descending
		if(pembanding == NULL){
			return;
		}
		else{
			while(pembanding != NULL){
				dibanding = pembanding->next;
				
				while(dibanding != NULL){
					if(strcmp(pembanding->nama, dibanding->nama) < 0){		//jika nama sebelum < sesudah, lakukan swap
						swap(pembanding, dibanding);
					}
					dibanding = dibanding->next;
				}
				pembanding=pembanding->next;
			}
		}
	}
}

void sorthargabuah(int sorttype){						//fungsi sort berdsarkan harga buah
	listbuah *pembanding, *dibanding;
	pembanding = headbuah;
	dibanding = NULL;
	
	if(sorttype == 1){									// jika 1, maka ascending
		if(pembanding == NULL){
			return;
		}
		else{
			while(pembanding != NULL){
				dibanding = pembanding->next;
				
				while(dibanding != NULL){
					if(pembanding->harga > dibanding->harga){			//jika harga sebelum<harga sesudah, maka swap
						swap(pembanding, dibanding);
					}
					dibanding = dibanding->next;
				}
				pembanding=pembanding->next;
			}
		}
	}
	else if(sorttype == 2){									//jika 2, maka descending
		if(pembanding == NULL){
			return;
		}
		else{
			while(pembanding != NULL){
				dibanding = pembanding->next;
				
				while(dibanding != NULL){
					if(pembanding->harga < dibanding->harga){			// jika harga sebelum > harga sesudah, maka swap
						swap(pembanding, dibanding);
					}
					dibanding = dibanding->next;
				}
				pembanding=pembanding->next;
			}
		}
	}
}
	
void sorttanggalbuah(int sorttype){							//fungsi melakukan sort berdsarkan tanggal masuk buah
	listbuah *pembanding, *dibanding;
	pembanding = headbuah;
	dibanding = NULL;
	
	if(sorttype == 1){										//jika 1, maka dari tanggal terdekat ke sekarang
		if(pembanding == NULL){
			return;
		}
		else{
			while(pembanding != NULL){
				dibanding = pembanding->next;
				
				while(dibanding != NULL){
					if(pembanding->yyin<dibanding->yyin){			//jika tahun sebelum< tahun sesudah, maka swap
						swap(pembanding, dibanding);
					}
					else if(pembanding->yyin == dibanding->yyin){	//jika bulan sebelum < bulan sesudah, maka swap
						if(pembanding->mmin<dibanding->mmin){
							swap(pembanding, dibanding);
						}
						else if(pembanding->mmin == dibanding->mmin){	//jika tanggal sebelum < tanggal sesudah, maka swap
							if(pembanding->ddin < dibanding->ddin){
								swap(pembanding, dibanding);
							}
						}
					}
					dibanding = dibanding->next;
				}
				pembanding=pembanding->next;
			}
	  	}
	}
	else if(sorttype == 2){										//jiak 2, maka dari tanggal terjauh dari sekarang
		if(pembanding == NULL){
			return;
		}
		else{
			while(pembanding != NULL){
				dibanding = pembanding->next;
				
				while(dibanding != NULL){
					if(pembanding->yyin>dibanding->yyin){				//jika tahun sebelum> tahun sesudah, maka swap
						swap(pembanding, dibanding);
					}
					else if(pembanding->yyin == dibanding->yyin){		//jika bulan sebelum> bulan sesudah, maka swap
						if(pembanding->mmin>dibanding->mmin){
							swap(pembanding, dibanding);
						}
						else if(pembanding->mmin == dibanding->mmin){	//jika tanggal sebelum> tanggal sesudah, maka swap
							if(pembanding->ddin > dibanding->ddin){
								swap(pembanding, dibanding);
							}
						}
					}
					dibanding = dibanding->next;
				}
				pembanding=pembanding->next;
			}
		}
	}
}

void searchnamabuah(char keyword[20]){					//function untuk mencari berdasarkan nama buah dari value keyword
	system("cls");
	header();			
	listbuah *temp;
	temp = headbuah;
	int i;
	char lowkeyword[20], lowname[20], name[20];			//digunakan agar jika keyword terdapat kapital maupun tidak sehingga bersifat case insensitive
	
	for(i=0;i<20;i++){
		lowkeyword[i]=tolower(keyword[i]);				//seluruh keyword dijadikan huruf kecil
	}
	
    if(temp == NULL){
		return;											//jika list masih kosong maka keluar dari function
	}
	else{	
		while(temp != NULL){							//mencari seluruh linked list
			strcpy(name, temp->nama);					//mengcopy data dari list buah pada char nama
			for(i=0;i<20;i++){
				lowname[i]=tolower(name[i]);			//mengecilkan huruf char nama
			}
			if(strstr(lowname, lowkeyword) != NULL){	//jika ada buah yang ditemukan maka masuk if
				tabel(temp);							//memanggil function print table dengan passing pointer listbuah
			}
			temp=temp->next;
		}
		printf("================================================================================================");
	}
}

void searchhargabuah(int range[2]){ 					//function untuk mencari berdasarkan range harga buah dari value range
	system("cls");
	header();
	listbuah *temp;
	temp = headbuah;
	
    if(temp == NULL){	
		return;											//jika list masih kosong maka keluar dari function
	}
	else{
		while(temp != NULL){							//mencari seluruh linked list
			if(temp->harga >= range[0] && temp->harga <= range[1]){		//jika ada buah yang ditemukan maka masuk if
				tabel(temp);
			}
			temp=temp->next;							//memanggil function print table dengan passing pointer listbuah
		}
		printf("================================================================================================");
	}
	free(temp);
}

void createlistpembeli(char namabuahbeli[], int idpembeli, float jumlahbeli, float hargatotal, int dataddbuy, int datammbuy, int datayybuy){
	listpembeli *node, *temp;					
	node = (listpembeli*)malloc(sizeof(listpembeli));		//mengalokasikan node baru terkait listpembeli
	strcpy(node->namabuah, namabuahbeli);					//menyimpan data-data informasi pada listpembeli
	node->id = idpembeli;
	node->jumlah = jumlahbeli;
	node->hargatotal = hargatotal;
	node->ddbuy = dataddbuy;
	node->mmbuy = datammbuy;
	node->yybuy = datayybuy;
	
	if(headpembeli == NULL){								//alokasikan jika merupakan list pertama
		headpembeli = node;
		headpembeli->next = NULL;
		return;
	}

	temp = headpembeli;

	while(temp->next != NULL){								//jika bukan list pertama maka akan traverse sampai akhir list
		temp = temp->next;
	}

	temp->next = node;										//alokasikan node tersebut pada list terakhir
	node->next = NULL;
}

void createlisthistogram(char namabuahbeli[], float jumlahbeli, float hargatotal){
	listhistogram *temp, *node;
	node = (listhistogram*)malloc(sizeof(listhistogram)); 	//mengalokasikan node baru terkait listhistogram
	int i;
	char lowkeyword[20], lowname[20], name[20];
	
	if(headhistogram == NULL){								//menyimpan data-data informasi pada listhistogram jika data baru
		strcpy(node->namabuah, namabuahbeli);				
		node->jumlah = jumlahbeli;
		node->hargatotal = hargatotal;
		headhistogram = node;
		headhistogram->next = NULL;
		return;
	}
	
	temp = headhistogram;
	
	for(i=0;i<20;i++){
		lowkeyword[i]=tolower(namabuahbeli[i]);			//untuk mencari jika akan ada buah yang dibeli sama
	}
	
    while (temp->next != NULL) {
    	strcpy(name, temp->namabuah);
    	for(i=0;i<20;i++){
			lowname[i]=tolower(name[i]);
		}
    	if (strstr(lowname, lowkeyword) != NULL) {		//jika ada buah yang ditemukan maka masuk if
	        temp->jumlah += jumlahbeli;					//akan dilakukan penambahan jika buah sudah terdapat dalam listhistogram
			temp->hargatotal += hargatotal;
	        return;
	    }
        temp = temp->next;
    }
    strcpy(name, temp->namabuah);
	for(i=0;i<20;i++){									
		lowname[i]=tolower(name[i]);
	}
	if (strstr(lowname, lowkeyword) != NULL) {			//jika ada buah yang ditemukan pada akhir list maka masuk if
        temp->jumlah += jumlahbeli;						//akan dilakukan penambahan jika buah sudah terdapat dalam listhistogram
		temp->hargatotal += hargatotal;
        return;
    }
    strcpy(node->namabuah, namabuahbeli);
	node->jumlah = jumlahbeli;
	node->hargatotal = hargatotal;
	temp->next = node;
	node->next = NULL;
}

void pembelibuah(int jmlp, int id, char buffer[]){
	const char s[2] = "/";
	char *token;			//untuk menyimpan char dalam pointer token
	int opsi, anchor = 0;
	int kesesuaian, errorjmlb = 0;
	
	int idpembeli;			//deklarasi untuk informasi terkait pembeli
	char namabuahbeli[20];
	float jumlahbeli;
	float hargatotal;
	int dataddbuy, datammbuy, datayybuy;

	listbuah *databuah;
	databuah = headbuah;
	
	token =strtok(buffer, s);		//untuk memisahkan char tanggal yang terdapat pada buffer yang dipass
	
	printf("================================================\n");
	while(databuah != NULL){
		if(id == databuah->id){
			while(kesesuaian != 1){
				strcpy(namabuahbeli, databuah->nama);

				while(errorjmlb!=1){
					printf("\nMasukkan Jumlah Pembelian (Sisir/Kg/Buah): ");
					scanf("%f", &jumlahbeli);
					if(jumlahbeli > databuah->jumlah){	// error handling jika membeli barang diluar jumlah stok
						printf("Jumlah Pembelian Melebihi Stok!");
					}
					else{
						errorjmlb=1;
					}
				}
				errorjmlb=0;
				
				while(token != NULL){		//untuk memecah char buffer tanggal
					
					if(anchor == 0){
						dataddbuy = atoi(token);	//char-char terpisah tersebut akan diubah menjadi int
					}
					else if(anchor == 1){
						datammbuy = atoi(token);
					}
					else{
						datayybuy = atoi(token);
					}
					token = strtok(NULL,s);
					anchor++;
				}
				
				//Hitung pembelian
				databuah->jumlah = databuah->jumlah - jumlahbeli;
				hargatotal = databuah->harga * jumlahbeli;
				idpembeli = databuah->id*100 + jmlp;	//data pembeli berdasarkan id buah dan jumlah pembelian
				
				printf("================================================================================================\n");
				printf("|                                           Rincian Pembeli                                     |\n", jmlp);
				printf("================================================================================================\n");
				printf("\nTanggal Pembelian: %d/%d/%d", dataddbuy, datammbuy, datayybuy);
				printf("\nID Pembeli: %d", idpembeli);
				printf("\nID Buah: %d", databuah->id);
				printf("\nTipe Buah: %s", namabuahbeli);
				printf("\nJumlah Pembelian (Sisir/Kg/Buah): %0.2f", jumlahbeli);
				printf("\nHarga Total Pembelian: Rp.%0.2f", hargatotal);
    
				printf("\n\nApakah pesanan anda sesuai? \n1) Ya \n2) Tidak\nInput anda: ");	//apakah pembelian buah sesuai atau tidak
				scanf("%d", &kesesuaian);
				
				if(kesesuaian == 1){
					printf("\nPesanan Anda Diterima!");
					//call function add pembeli & add histogram
					createlistpembeli(namabuahbeli, idpembeli, jumlahbeli, hargatotal, dataddbuy, datammbuy, datayybuy);
					printf("\nAdded to list pembeli");
					createlisthistogram(namabuahbeli, jumlahbeli, hargatotal);
					printf("\nAdded to list histogram");
					return;
				}
				else if (kesesuaian == 2){
					printf("\nUlang Kembali!");
					getch();
				}
				else{	//error handling
					fflush(stdin);
					printf("\nInvalid Input!");
					getch();
				}
			}
		}
		databuah = databuah->next;
	}
}

#endif
