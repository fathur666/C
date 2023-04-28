#include <stdio.h> 
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "h1.h"

int main(){
	time_t timer;							//Untuk menunjukkan waktu saat ini dari sistem yang dijalankan
    char buffer[26];
    struct tm* tm_info;
    
    char datanama[15][25]={										//Array 2D terkait buah-buah yang digunakan
	"Pisang Raja", "Pisang Ambon",
	"Semangka Kuning",
	"Melon Hijau",
	"Apel Fuji", "Apel Manalagi", "Apel Royal Gala",
	"Buah Naga Merah", "Buah Naga Putih",
	"Anggur Jupiter",
	"Nanas Bogor",
	"Alpukat Wina", "Alpukat Mentega",
	"Jeruk Medan", "Jeruk Mandarin"
	};
	int dataid[15]={									//Array 2D: indeks[0]=ID; indeks[1]=Jumlah; Indeks[2]=Harga
	101, 102,
	201,
	301,
	401, 402, 403,
	501, 502,													//Penaman ID yaitu No.ID+0+No.Jenis
	601,
	701,
	801, 802,
	901, 902};
	float datajumlah[15]={
	5, 6,													//Jumlah masing-masing buah
	3,
	5,
	10, 4, 4,
	8, 4,
	3,
	15,
	8, 2,
	5, 4};
	int dataharga[15]={
	21000, 25000,										//Harga masing-masing buah
	26000,
	24000, 
	28000, 30000, 36000,
	18000, 80000,
	75000,
	7500,
	20000, 20000,
	33600, 53100};
	int datatanggal[15][3]={								 	//Tanggal masuk masing-masing buah
	{3, 12, 2021}, {4, 12, 2021},
	{1, 12, 2021},
	{5, 12, 2021}, 
	{5, 12, 2021}, {30, 11, 2021}, {6, 12, 2021},
	{5, 12, 2021}, {7, 12, 2021},
	{1, 12, 2021},
	{6, 12, 2021}, 
	{6, 12, 2021}, {4, 12, 2021}, 
	{2, 12, 2021}, {2, 12, 2021},
	};

	int jmlp, jmlh, loc, key;
	int id, harga;
	float jumlah; 
	char nama[20], tanggalmasuk[20];
	int kategori, opsi1, opsi3;
	int sortmethod, sorttype, kesesuaian, temp;
	int searchmethod, searchKey, range[2];
	char keyword[20];
	int i, j, exit=0, sen=0, errorjmlb=0;  
	int dataddin, datammin, datayyin;
	
	for(i=0;i<15;i++){					//Memasukkan data-data yang terdapat pada array kedalam linked list buah
		strcpy(nama, datanama[i]);
		id = dataid[i];
		jumlah = datajumlah[i];
		harga = dataharga[i];
		dataddin = datatanggal[i][0];
		datammin = datatanggal[i][1];
		datayyin = datatanggal[i][2];
		createlistbuah(nama, id, jumlah, harga, dataddin, datammin, datayyin);
		j++;
	}
	
	masukadmin();
	
	while(exit!=6){
		kategori = 0;
		system("cls");
		printf("============================================================\n");	//Main Menu Program
	    printf("||              SISTEM ADMINISTRASI TOKO BUAH             ||\n");
		printf("============================================================\n");		
		printf("1) Beli Buah \n2) Riwayat Penjualan \n3) Update Buah \n4) Delete Buah \n5) Help \n6) Exit");		//Opsi Pilihan Menu
		printf("\n\nPilih Kategori Yang Anda Inginkan Sesuai Dengan Nomor: ");
		scanf("%d", &kategori);

		switch(kategori){
			case 1:
				sen = 0;
				while(sen!=4){
					system("cls");
					header();
					printlistbuah();
					printf("================================================================================================");
					printf("\n\nPilih Opsi Yang Anda Inginkan Sesuai Dengan Nomor!");
					printf("\n1)Sort \n2)Search \n3)Beli Buah \n4)Exit");				//Program menunjukkan seluruh buah pada toko
					printf("\nPilihan Anda: ");											//User diberikan opsi untuk sort, search, dan beli
					scanf("%d", &opsi1);
					
				switch(opsi1){
						case 1: 		//Opsi Sort Buah
							printf("================================================================================================\n");
							printf("\n\nPilih Opsi Yang Anda Inginkan Sesuai Dengan Nomor!");
							printf("\n1)Sort Nama Buah \n2)Sort Harga \n3)Sort Tanggal Masuk \n4)Exit");
							printf("\nPilihan Anda: ");
							scanf("%d", &sortmethod);
					
							if(sortmethod == 1){	// Sort Berdasarkan Nama Buah
								printf("================================================================================================\n");
								printf("\nPilih Tipe Sort Yang Anda Inginkan Sesuai Dengan Nomor!");
								printf("\n1) A-Z(Ascending) \n2) Z-A(Descending)");
				            	printf("\nPilih Tipe Sort Nama Buah: ");
				           		scanf("%d", &sorttype);
								sortnamabuah(sorttype);
							}
							else if(sortmethod == 2){	// Sort Berdasarkan Harga Buah
								printf("================================================================================================\n");
								printf("\nPilih Tipe Sort Yang Anda Inginkan Sesuai Dengan Nomor!");
								printf("\n1) Low-High(Ascending) \n2) High-Low(Descending)");
				            	printf("\nPilih Tipe Sort Harga Buah: ");
				           		scanf("%d", &sorttype);
								sorthargabuah(sorttype);
							}
							else if (sortmethod == 3){	// Sort Berdasarkan tanggal masuk buah
								printf("================================================================================================\n");
								printf("\nPilih Tipe Sort Yang Anda Inginkan Sesuai Dengan Nomor!");
								printf("\n1) Nearest Date \n2) Furthest Date");
				            	printf("\nPilih Tipe Sort Tanggal Masuk: ");
				           		scanf("%d", &sorttype);
								sorttanggalbuah(sorttype);
					
							}
							else if (sortmethod == 4){	// exit dari sort
								printf("\n\nPress Any Key to Continue...");
								getch();
							}
							else{	//error handling
								fflush(stdin);
								printf("\nInvalid Input!");
								getch();
							}
							sortmethod = 0;
							sorttype = 0;
							break;
						case 2: // Opsi Search Buah
							printf("================================================================================================\n");
							printf("1)Nama Buah \n2)Harga \n3)Exit");
							printf("\n\nPilih Tipe Search Yang Anda Inginkan Sesuai Dengan Nomor: ");
							scanf("%d", &searchmethod);	

							if(searchmethod == 1){ // Search berdasarkan nama buah
								printf("================================================================================================\n");
								printf("Search Berdasarkan Nama Buah\n");
								printf("Nama yang anda ingin cari: \n");
								scanf("%s", &keyword);
								searchnamabuah(keyword);
								printf("\n\nPress Any Key to return to the list...");
								getch();
							}
							else if(searchmethod == 2){ // Search berdasarkan range harga buah
								printf("================================================================================================\n");
								printf("Pilih Interval (Bottom <Harga Buah< Top)\nBottom= ");
								scanf("%d", &range[0]);
								printf("Top= ");
								scanf("%d",  &range[1]);
								searchhargabuah(range);
								printf("\n\nPress Any Key to return to the list...");
								getch();
							}
							else if (searchmethod == 3){ // exit search
								printf("\n\nPress Any Key to Continue...");
								getch();
							}
							else{	// error handling
								fflush(stdin);
								printf("\nInvalid Input!");
								getch();
							}
							searchmethod = 0;
							sorttype = 0;	
							break;
						case 3:
							jmlp++;
							//display item yang mau dibeli
							printf("================================================================================================\n");
							printf("Nama yang anda ingin cari: \n");
							scanf("%s", &keyword);
							searchnamabuah(keyword);
							
							timer = time(NULL);
						    tm_info = localtime(&timer);
						    strftime(buffer, 26, "%d/%m/%Y", tm_info);
						    printf("\nMasukkan ID dari Buah: ");
							scanf("%d", &id);
							
							pembelibuah(jmlp, id, buffer);
							
							printf("\nPembeli Updated");
							getch();
							
							break;
						case 4:
							sen=4;
							break;
						default:
							fflush(stdin);
							printf("Invalid Input!\n");		//Error Handling
	            			getch();
							break;
					}	
				}
				break;
			case 2:
				system("cls");
				printlistpembeli();
				printlisthistogram();
				printf("\n\nPress Any Key to Continue...\n");
				getch();
				break;
			case 3:
				sen = 0;
				while(sen!=3){
					system("cls");
					header();
					printlistbuah();
					printf("================================================================================================");
					printf("\n\nRestock Buah Lama atau Buah Baru?");
					printf("\n1)Buah Lama \n2)Buah baru \n3)Exit");				//Program menunjukkan seluruh buah pada toko
					printf("\nPilihan Anda: ");											//User diberikan opsi untuk sort, search, dan beli
					scanf("%d", &opsi3);
					switch(opsi3){
						case 1:
							printf("\nMasukkan ID dari Buah: ");
							scanf("%d", &id);
							timer = time(NULL);
						    tm_info = localtime(&timer);
						    strftime(buffer, 26, "%d/%m/%Y", tm_info);
							updatebuahlama(id, buffer);
							printf("\nList Updated");
							getch();
							break;
						case 2:
							timer = time(NULL);
						    tm_info = localtime(&timer);
						    strftime(buffer, 26, "%d/%m/%Y", tm_info);
							updatebuahbaru(buffer);
							printf("\nList Updated");
							getch();	
							break;
						case 3:
							sen = 3;
							break;
						default:
							fflush(stdin);
							printf("\nInvalid Input!");
							getch();
							break;
					}
				}
				break;
			case 4:
				system("cls");
				header();
				printlistbuah();
				printf("================================================================================================");
				printf("\nMasukkan ID dari Buah (-1 to cancel delete): ");
				scanf("%d", &id);
				if(id == -1){
					break;
				}
				else{
					deletebuah(id);
					printf("\nDelete Succesful");
					getch();
					break;	
				}
			case 5:
				system("cls");
            	printf("|| MENU PENJELASAN PROGRAM ||");
                printf("\n========================================\n");
				printf("1) Program ini merupakan simulasi penjualan di toko buah.\n");
				printf("2) Menu 1 merupakan menu untuk menampilkan list buah yang berisikan tabel id, nama, harga/kg, jumlah (kg) dan tanggal diterimanya buah.\n");
				printf("3) Pada Menu 1, terdapat pilihan untuk melakukan sorting, searching ataupun pembelian buah oleh pelanggan\n");
				printf("4) Menu 2 merupakan menu untuk menampilkan riwayat penjualan dengan tabel yang berisikan tanggal beli, nama, kuantitas, total pembelian buah.\n");
				printf("5) Pada Menu 2, terdapat pilihan untuk menampilkan dalam hasil penjualan dalam histogram.\n");
				printf("6) Menu 3 merupakan menu untuk melakukan update buah yang lama ataupun baru\n");
				printf("7) Hal yang diupdate adalah nama buah, jumlah, dan harga\n");
				printf("8) Menu 4 merupakan menu untuk menghapus buah yang ada di list\n");
				printf("9) Menu 5 merupakan menu untuk menampilkan menu penjelasan proram untuk mengetahui penjelasan dari bagian-bagian dalam program.\n");
				printf("10) Menu 6 merupakan menu untuk keluar dari program\n");
				printf("\n\nPress Any Key to Continue...\n");		//Error Handling
            	getch();
				break;
			case 6:
				exit = 6;
            	break;
			default:
				fflush(stdin);
				printf("Invalid Input!\n");		//Error Handling
            	getch();
                break;
		}
	}
	return 0;
}

