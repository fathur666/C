#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

//Data untuk Mobil
typedef struct {  
	char nama[50];	
	char gear[20];
	char plat[20];
	int tahun;
	int harian;
	int hsopir;
	int kapasitas;
	char status[20]; 
}kendaraan;

//Data untuk Tanggal
typedef struct {
	int dd;
	int mm;
	int yy;
}tanggal;

//Data untuk Peminjam
typedef struct {
	char nama[50];
	unsigned long long int nik;
	unsigned long long int nohp;
	int ikendaraan;
	char tipe[50];
	int durasi;
}manusia;

void removepeminjam(manusia *peminjam, int i, int jmlp);		//Menghilangkan Peminjam dengan metode remove and drag
void cekmobil(kendaraan *mobil, int i);		//Menampilkan data mobil menggunakan printf
void cekpeminjam(manusia *peminjam, kendaraan *mobil, int i);			//Menampilkan data peminjam menggunakan printf
void biaya(manusia *peminjam, tanggal *date, tanggal waktu, int durasi, int jmlp);	//Menghitung durasi peminjaman untuk biaya
void formmobil(kendaraan *mobil, int jmlm);		//Memasukkan Data mobil menggunakan scanf
void removemobil(kendaraan *mobil, int i, int jmlm);		//Menghilangkan data mobil menggunakan metode remove and drag

int main(){  
	int exit=0, kategori, i, j, p1, p2, p3, n=100, temp;
	int durasi=0, total=0, bayar=0;
	int jmlm=0, jmlp=0;
	int optb11, optb12, optb2;
	int ir, next;
	char yn[1];
	
	kendaraan *mobil, car;
	tanggal *date, waktu;
	manusia *peminjam;
	mobil = (kendaraan*)malloc(n * sizeof(kendaraan));
	date =(tanggal*)malloc(4*sizeof(tanggal));
	peminjam = (manusia*)malloc(n * sizeof(manusia));
	
   while(exit != 5){
    	    system("cls");	//Membersihkan Layar
    	    printf("|| SISTEM DATA PEMINJAMAN MOBIL ||\n");		//Menampilkan Main Menu
			printf("1)Sewa Mobil \n2)Add/Remove \n3)List Mobil \n4)List Peminjam \n5)Exit");
   			printf("\n\nPilih Kategori Yang Anda Inginkan Sesuai Dengan Nomor: ");
    		scanf("%d", &kategori);
    		
        switch(kategori){
            case 1:	//Pilih untuk menambahkan/mengurangi data peminjam 
            	menu1:
				system("cls");
				printf("|| SISTEM DATA PEMINJAMAN MOBIL ||\n || Menu Sewa Mobil ||\n");
                printf("1)Penyewaan \n2)Pengembalian \n3)Kembali \nPilihan Anda: ");
                scanf("%d", &p1);
                
                switch(p1){
                	case 1:		//pilih untuk menambahakn data pmeinjam dan menghitung biaya rental
                		menu11:
                		jmlp++;		//penambahan jumlah peminjam mobil
	                	system("cls");
	                	printf("|| SISTEM DATA PEMINJAMAN MOBIL ||\n");	
	                	printf("Nama Peminjam		: ");
	                	scanf("%d", &temp);
	                	scanf("%[^\n]", &(peminjam+jmlp)->nama);
	                	printf("Nomor Induk Keluarga	: ");
	                	scanf("%llu", &(peminjam+jmlp)->nik);
	                	printf("Nomor HP Peminjam	: ");
	                	scanf("%llu", &(peminjam+jmlp)->nohp);
	                	choice1: printf("Mobil Pilihan Peminjam Sesuai Index: ");
		                scanf("%d", &(peminjam+jmlp)->ikendaraan);
					    i=(peminjam+jmlp)->ikendaraan;					//pilihan kendaraan berdasarkan list diassign ke var i
					    
					    if(strcmp((mobil+i)->status, "Terpinjam") == 0){	//error handling untuk kasus mobil yang sudah terpinjam
					    	jmlp--;
							printf("\nMobil Sudah Terpinjam!");
					    	printf("\nPress Any Key To Continue...");
					    	getch();
							goto menu1;
						}
						else{
							cekmobil(mobil, i);		//call function untuk display rincian mobil yang telah dipilih
						    YN1: printf("\nApakah Ingin Memilih Mobil Di atas? (Y|N): ");
						    scanf("%s", &yn);
			
							if(strcmp(yn, "Y") == 0){	
								biaya(peminjam, date, waktu, durasi, jmlp);	//call function untuk melakukan kalkulasi durasi waktu berdasarkan tanggal
								printf("\nLama Peminjaman: %d hari\n", peminjam[jmlp].durasi);
								b1: printf("\nPilih Biaya!\n1)Harian\n2)Harian+Supir");
								printf("\nPilihan Anda: ");
								scanf("%d", &bayar);
								switch (bayar){
									case 1:
										strcpy(peminjam[jmlp].tipe, "Harian");			//menempatkan tipe pilihan paket yang dipilih customer
										total= peminjam[jmlp].durasi*mobil[i].harian;
										printf("\nTotal Harga: Rp%d", total);
										strcpy(mobil[i].status, "Terpinjam");			//merubah status dari mobil
										break;
									case 2:
										strcpy(peminjam[jmlp].tipe, "H+Sopir");			//menempatkan tipe pilihan paket yang dipilih customer
										total= peminjam[jmlp].durasi*mobil[i].hsopir;
										printf("\nTotal Harga: Rp%d", total);
										strcpy(mobil[i].status, "Terpinjam");			//merubah status dari mobil
										break;
									default:
										printf("Invalid Input!");
										goto b1;		//error handling, kembali ke pilihan paket								
										break;
								}
								printf("\n---------------------------------------");
		                        printf("\nPeminjam Telah Ditambahkan ke Dalam List!\n");
		                        printf("1)Tambah Lagi \n2)Kembali \n3)Menu Utama");
		                        optb11 = 0;
		                        while(optb11 !=1 && optb11 !=3){
		                        	printf("\nPilihan Anda: ");
			                        scanf("%d", &optb11);
			                        if(optb11 == 1){
			                            goto menu11;	//kembali ke menu penambahan
			                        }
			                        else if(optb11 ==2){
			                        	goto menu1;		//kembali ke menu penambahan/pengurangan
									}
			                        else if(optb11 != 1 && optb11!=3){	//error handling
			                        	printf("Invalid Input");
									}
								}
							}
							else if(strcmp(yn, "N") == 0){
								goto menu1;
							}
							else{
								printf("Invalid Input!");
								goto YN1;	//error handling
							}
						}
                		break;
                	case 2:		//pilih untuk mengubah status data peminjam sebagai pengembalian mobil*
                		menu12:
                		system("cls");
                		printf("|| SISTEM DATA PEMINJAMAN MOBIL ||\n");
                     	printf("Masukkan Index Peminjam: ");
                        scanf("%d", &ir);
                        i=ir;
						cekpeminjam(peminjam, mobil, i);                  //call function untuk mendisplay data sang peminjam
			            YN01: printf("\nApakah Ingin Menghapus Peminjam Diatas? (Y|N): ");
			            scanf("%s", &yn);
			            if(strcmp(yn, "Y") == 0){
							strcpy(mobil[i].status, "Tersedia"); //merubah status kendaraan yang dikembalikan
			            	removepeminjam(peminjam, i, jmlp);			//call function untuk mengkosongkan isi data peminjam
	                        jmlp-=1;
							printf("\n---------------------------------------");
		                    printf("\nPeminjam Telah Dihapus Dari Dalam List!\n");
		                    printf("1)Hapus Lagi \n2)Kembali \n3)Menu Utama");
		                    optb12 = 0;
		                    while(optb12 !=1 && optb12 !=3){
			                    printf("\nPilihan Anda: ");
				                scanf("%d", &optb12);
				                if(optb12 == 1){
				                	goto menu12; //kembali ke menu penghapusan data peminjam
								}
								else if(optb12 == 2){
				                    goto menu1;
				                }
				                else if(optb12 != 1 && optb12!=3){
				                  	printf("Invalid Input");
								}
							}
						}
						else if(strcmp(yn, "N") == 0){
							goto menu1;
						}
                        else {
                        	printf("Invalid Input!");
                        	goto YN01;
						}               		
                		break;
				   case 3:
		            	break;
		            default :
		            	printf("Invalid Input!");
		            	getch ();
		            	goto menu1;
		            	break;        
				}    
                break;         
           
            case 2:		//Pilih untuk menambah/mengurangi mobil pada list mobil
                menu2:
                system("cls");
                printf("|| SISTEM DATA PEMINJAMAN MOBIL ||\n || Menu Add/Remove ||\n");		//Menampilkan Menu Add/Remove Mobil
                printf("1)Add Kendaraan \n2)Remove Kendaraan \n3)Kembali \nPilihan Anda: ");
                scanf("%d", &p2);
                switch(p2){
                    case 1:		//Menambahkan Mobil Pada List Mobil
                    	optb2 = 0;
	                    while(optb2 != 3){
	                    	system("cls");
	                        jmlm += 1;
							formmobil(mobil, jmlm);		//Mengisi data mobil
	                        printf("\nMobil Telah Ditambahkan ke Dalam List!\n");
	                        printf("1)Tambah Lagi \n2)Kembali \n3)Menu Utama");		//Opsi Kembali
	                        optb2 = 0;
	                        while(optb2 !=1 && optb2 !=3){
	                        	printf("\nPilihan Anda: ");
		                        scanf("%d", &optb2);
		                        if(optb2 == 2){
		                            goto menu2;
		                        }
		                        else if(optb2 != 1 && optb2!=3){
		                        	printf("Invalid Input");
								}
							}
	                    }
                        break;

                    case 2:			//Menghilangkan Mobil pada List Mobil*
                    	optb2 = 0;
                    	menu22:
                    	while( optb2 != 3){
                    		system("cls");
                    		printf("|| SISTEM DATA PEMINJAMAN MOBIL ||\n");
	                    	printf("Masukkan Index Mobil: ");	//Memilih Mobil yang akan dihilangkan berdasarkan index pada list mobil
	                        scanf("%d", &ir);
							i=ir;
							cekmobil(mobil,i);
				            YN2: printf("\nApakah Ingin Menghapus Mobil Diatas? (Y|N):");
				            scanf("%s", yn);
				            if(strcmp(yn, "Y") == 0){
								removemobil(mobil, i, jmlm);	//Fungsi untuk Menghilangkan Mobil dari list
		                        jmlm -= 1;
		                        printf("\n---------------------------------------\n");
			
			                    printf("\nMobil Telah Dihapuskan Dari Dalam List!\n");
			                    printf("1)Hapus Lagi \n2)Kembali \n3)Menu Utama");		//Opsi Kembali
								while(optb2 !=1 && optb2 !=3){
									printf("\nPilihan Anda: ");
									scanf("%d", &optb2);
									if(optb2 == 2){
										goto menu2;
									}
									else if(optb2 != 1 && optb2 !=3){
										printf("Invalid Input");
									}
								}
							}
							else if(strcmp(yn, "N") == 0){
								goto menu2;
							}
	                        else {
	                        	printf("Invalid Input!");
	                        	goto YN2;
							}	
						}
                        break;
	                 case 3:
			          	break;
			         default :
			           	printf("Invalid Input!");
			           	getch ();
			           	goto menu2;
			           	break;        
                }
                break;
            case 3:		//Pilih untuk menampilkan semua mobil yang ada pada list setelah ditambahkan/dihilangkan
            	system("cls");
            	printf("\t|| DAFTAR MOBIL ||");
                printf("\n=======================================\n");
                for(i=1;i<=jmlm;i++){
               	 	cekmobil(mobil, i);		//fungsi untuk menampilkan list mobil
            	}
				printf("\n\nPress Any Key to Continue...");
				getch();
                break;
            case 4:		//pilih untuk menampilkan semua peminjam yang ad apada list setelah peminjaman/pengembalian
             	system("cls");
            	printf("\t||DAFTAR PEMINJAM||");
                printf("\n========================================\n");
                for(i=1;i<=jmlp;i++){
                    cekpeminjam(peminjam, mobil, i);		//fungsi untuk menampilkan list peminjam
				}
				printf("\n\nPress Any Key to Continue...");
				getch();           	
                break;
            case 5:		//Keluar
            	exit = 5;
            	break;
            default: 
            	printf("Invalid Input!\n");		//Error Handling
            	getch();
                break;
        }
    }
    return 0;
}

void biaya(manusia *peminjam, tanggal *date, tanggal waktu, int durasi, int jmlp){		//Menghitung durasi peminjaman untuk biaya* (improve tanggal)
	durasi=0;
	time_t t;
	time(&t);
	printf("\nTanggal Hari Ini: %s", ctime(&t));
	printf("Tanggal Pinjam (DD/MM/YYYY) :");
	scanf("%d/%d/%d", &(date+1)->dd, &(date+1)->mm, &(date+1)->yy);
	printf("Tanggal Kembali (DD/MM/YYYY) :");
	scanf("%d/%d/%d", &(date+2)->dd, &(date+2)->mm, &(date+2)->yy);
	
	if((date+2)->dd < (date+1)->dd){		//Menghitung durasi dengan mengurangi tanggal pinjam terhadap tanggal sewa
		(date+2)->mm -=1;					
		(date+2)->dd += 30;
	}
	durasi += (date+2)->dd - (date+1)->dd;	
	if((date+2)->mm < (date+1)->mm){
		(date+2)->yy -=1;
		(date+2)->mm += 12;
	}
	durasi += ((date+2)->mm - (date+1)->mm)*30;
	durasi += ((date+2)->yy - (date+1)->yy)*365;
	peminjam[jmlp].durasi = durasi;
}

void cekmobil(kendaraan *mobil, int i){		//Menampilkan data mobil menggunakan printf
	printf("\n\tMobil ke-%d ", i);
	printf("\n---------------------------------------");
	printf("\nTipe Mobil		: %s", (mobil+i)->nama);
	printf("\nGear			: %s", (mobil+i)->gear);
	printf("\nPlat			: %s", (mobil+i)->plat);
	printf("\nTahun			: %d", (mobil+i)->tahun);
	printf("\nKapasitas		: %d", (mobil+i)->kapasitas);
	printf("\nStatus			: %s", (mobil+i)->status);
	printf("\nBiaya Harian		: Rp. %d", (mobil+i)->harian);
	printf("\nBiaya Harian+Sopir	: Rp. %d\n", (mobil+i)->hsopir);
}

void cekpeminjam(manusia *peminjam, kendaraan *mobil, int i){		//Menampilkan data peminjam menggunakan printf
	printf("\n\tPeminjam ke-%d ", i);
	printf("\n---------------------------------------");
	printf("\nNama Peminjam		: %s", (peminjam+i)->nama);
	printf("\nNomor Induk Keluarga	: %llu", (peminjam+i)->nik);
	printf("\nNomor HP		: %d", (peminjam+i)->nohp);
	printf("\nTipe Mobil Dipinjam	: %s", (mobil+(peminjam[i].ikendaraan))->nama);
	printf("\nGear			: %s", (mobil+(peminjam[i].ikendaraan))->gear);
	printf("\nPlat			: %s", (mobil+(peminjam[i].ikendaraan))->plat);
	printf("\nTipe Peminjaman		: %s", (peminjam+i)->tipe);
	printf("\nDurasi Peminjaman	: %d Hari\n", (peminjam+i)->durasi);
}

void removepeminjam(manusia *peminjam, int i, int jmlp){		//Menghilangkan Peminjam dengan metode remove and drag
	while(i<=jmlp){
  		memset(&peminjam[i].nama, 0, sizeof(peminjam[i].nama));		//menghapus semua data peminjam pada index yang telah dipilih
        memset(&peminjam[i].nik, 0, sizeof(peminjam[i].nik));
        memset(&peminjam[i].nohp, 0, sizeof(peminjam[i].nohp));
        memset(&peminjam[i].ikendaraan, 0, sizeof(peminjam[i].ikendaraan));
		memset(&peminjam[i].tipe, 0, sizeof(peminjam[i].tipe));
		memset(&peminjam[i].durasi, 0, sizeof(peminjam[i].durasi));
                        		
		strcpy(peminjam[i].nama, peminjam[i+1].nama);			//Mendrag data peminjam yang ada di bawah ke atas
        peminjam[i].nik = peminjam[i+1].nik;
        peminjam[i].nohp = peminjam[i+1].nohp;
        peminjam[i].ikendaraan = peminjam[i+1].ikendaraan;
        strcpy(peminjam[i].tipe, peminjam[i+1].tipe);
        peminjam[i].durasi = peminjam[i+1].durasi;
		i++;			
	}
}

void formmobil(kendaraan *mobil, int jmlm){		//Memasukkan Data mobil menggunakan scanf
	int temp;
	printf("|| SISTEM DATA PEMINJAMAN MOBIL ||\n");
	printf("Tipe Kendaraan		: ");
	scanf("%d", &temp);
	scanf("%[^\n]", &(mobil+jmlm)->nama);
	printf("Model Kendaraan		: ");
	scanf("%d", &temp);
	scanf("%[^\n]", &(mobil+jmlm)->gear);
	printf("Plat Kendaraan		: ");
	scanf("%d", &temp);
	scanf("%[^\n]", &(mobil+jmlm)->plat);
	printf("Tahun Kendaraan		: ");
	scanf("%d", &(mobil+jmlm)->tahun);
	printf("Biaya Harian		: ");
	scanf("%d", &(mobil+jmlm)->harian);
	printf("Biaya Harian + Sopir	: ");
	scanf("%d", &(mobil+jmlm)->hsopir);							
	printf("Kapasitas Penumpang	: ");
	scanf("%d", &(mobil+jmlm)->kapasitas);
	printf("Kondisi Kendaraan	: ");
	scanf("%d", &temp);
	scanf("%[^\n]", &(mobil+jmlm)->status);
	printf("\n---------------------------------------\n");
}

void removemobil(kendaraan *mobil, int i, int jmlm){		//Menghilangkan data mobil menggunakan metode remove and drag
	while(i<=jmlm){
	    memset(&mobil[i].nama, 0, sizeof(mobil[i].nama));		//menghapus semua data mobil pada index yang telah dipilih
	    memset(&mobil[i].gear, 0, sizeof(mobil[i].gear));
	    memset(&mobil[i].plat, 0, sizeof(mobil[i].plat));
		memset(&mobil[i].tahun, 0, sizeof(mobil[i].tahun));
		memset(&mobil[i].harian, 0, sizeof(mobil[i].harian));
		memset(&mobil[i].hsopir, 0, sizeof(mobil[i].hsopir));
	    memset(&mobil[i].kapasitas, 0, sizeof(mobil[i].kapasitas));
	    memset(&mobil[i].status, 0, sizeof(mobil[i].status));
	                        		
		strcpy(mobil[i].nama, mobil[i+1].nama);			//Mendrag data mobil yang ada di bawah ke atas
	    strcpy(mobil[i].gear, mobil[i+1].gear);
		strcpy(mobil[i].plat, mobil[i+1].plat);
	    mobil[i].tahun = mobil[i+1].tahun;
		mobil[i].harian = mobil[i+1].harian;
		mobil[i].hsopir = mobil[i+1].hsopir;
	    mobil[i].kapasitas = mobil[i+1].kapasitas;
	    strcpy(mobil[i].status, mobil[i+1].status);	
		
		i++;							
	}
}
