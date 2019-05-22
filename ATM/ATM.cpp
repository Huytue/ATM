//Khai bao thu vien:
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <stdio.h>
#include <ctime>
#include <windows.h>
#include <iomanip>
using namespace std;

//Khai bao CTDL:
struct KhachHang
{
	string sUser;
	string sPass;
	string sSTK;	
	string sHoTen;
	int fSoDu;
	string sLoaiTien;
	string sChiNhanh;
};
struct Node
{
	KhachHang nData; 
	Node * pNext;	
};
Node * createNode(KhachHang kH)
{
	Node *p = new Node;
	if (p == NULL)
		exit(1);
	p->nData = kH; 
	p->pNext = NULL; 
	return p;
}
struct List
{
	Node *pHead, *pTail;
	List()
	{
		pHead = pTail = NULL;
	}
};

/*------------Thong tin ATM---------------*/
string sMaATM = "998091"; //Ma tru ATM
void nhapKH(ifstream &fin, KhachHang &kH);
void nhapDSKH(ifstream &fin, List &L);
void textcolor(int color);
void ghiKH(List &L);
void addTail(List &L, KhachHang kH);
void xuatDSKH(List L);
void xuatKH(KhachHang kh);
int maGiaodich();
void thongBao(string sVien);
int nDemSoLuongKhachHang();
//1.Chuc nang dang nhap: 
string maHoaMK(unsigned int maxLength);
void dangNhap(List L);
//2.Chuc nang rut tien:
void rutTien(List L, Node * q);
//3.Chuc nang chuyen tien:
void chuyentien(List L, Node* q);
//4.Chuc nang xem noi dung giao dich:
void ghiLSGD(List L, Node* q, string sChucNang, int nTienTru, Node* g, int nPhiGD);
//5.Chuc nang them:
void doiMatKhau(List L, Node * t);
void thongTinTK(List L, Node * q);
void docLichSuGiaoDich(Node * q);
void inHoaDon(List L, Node * q, int nTienRut, int PhiGD,  Node * g, string sForm);
int nPhiGiaoDich(int nTienNhap, string sForm);
string kiemTraTime(string s, Node * q);
void recharge(List L, Node * q);



//Chuong trinh chinh:
void main()
{
	List L;
	ifstream fin; 
	fin.open("input.dat");
	nhapDSKH(fin, L); 
	fin.close();
	dangNhap(L);
	//xuatDSKH(L);
	system("pause");
}



//1.Chuc nang dang nhap 
void dangNhap(List L)
{
	int nChon = 0;
	int i = 0;
	int nLan = 2;
	string sUsername = " ";
	string sPassword = " ";
	int flag = 0;
	int nDem = 0;
	thongBao("LOGIN");
	cout << "\t\t\tLuu y: Nhap ";
	textcolor(4);
	cout << "ESC";
	textcolor(7);
	cout << " de thoat khoi chuong trinh\n" << endl;
	while(i < 3)
	{
		textcolor(2);
		cout << "\t\t\tNhap tai khoan: ";
		textcolor(7);
		rewind(stdin);
		getline(cin, sUsername);
		if (sUsername == "ESC" || sUsername == "esc")
		{
			textcolor(10);
			cout << "\n\t\t\tCam On Quy Khach Da Su Dung Dich Vu Hen Gap Lai " << endl;
			i = i + 4;
			textcolor(7);
		}
		else
		{
			textcolor(2);
			cout << "\t\t\tNhap password: ";
			textcolor(7);
			sPassword = maHoaMK(6);
			for(Node * p = L.pHead; p != NULL; p = p->pNext)
			{
			 if(sUsername == p->nData.sUser && p->nData.sPass == "locked")
			 {
				 textcolor(4);
				 cout << "\t\tTai khoan nay da bi khoa. Vui Long Lien He: 0988.2.33.77 !!!\a\n\n";
				 textcolor(7);
				 i +=4;
				 break;
			 }
			 else if(sUsername == p->nData.sUser && sPassword == p->nData.sPass)
				{
					nDem += 5;
					Node * q = p;
					i += 4;
					flag = 0;
					do {	
						system("cls");
						cc:
						textcolor(10);
						cout << "\t\t\tLogin Thanh Cong - Welcom To TDC \n" << endl;
						textcolor(7);
						thongBao("MENU");
						textcolor(10);
						cout << "\t\t\tNhap so de thuc hien: ";
						textcolor(7);
						cin >> nChon;					
					} while(nChon < 1 || nChon > 7);
					string sLuaChon = "";
					switch(nChon)
					{
					case 1:
						system("cls");
						//Thong tin tai khoan
						thongTinTK(L, q);
						textcolor(9);
						cout << "\n\n\t\tNhap \""; textcolor(10); cout << "YES"; textcolor(9); cout << "\" de quay lai Menu. Nhap \""; textcolor(4); cout << "NO"; textcolor(9); cout << "\" de thoat: "; textcolor(7);
						rewind(stdin); getline(cin, sLuaChon);
						if (sLuaChon == "yes" || sLuaChon == "YES")
						{
							system("cls");
							goto cc;
						}
						else
						{
							textcolor(10);
							cout << "\n\t\t\tCam on quy khach da su dung dich vu, hen gap lai. \n";
							textcolor(7);
							break;
						}
					case 2:
						system("cls");
						//Rut tien
						rutTien(L, q);
						textcolor(9);
						cout << "\n\n\t\tNhap \"";textcolor(10); cout << "YES"; textcolor(9); cout << "\" de quay lai Menu. Nhap \""; textcolor(4); cout << "NO"; textcolor(9); cout << "\" de thoat: "; textcolor(7);
						rewind(stdin); getline(cin, sLuaChon);
						if(sLuaChon == "yes" || sLuaChon == "YES")
						{
							system("cls");
							goto cc;
						}
						else 
						{
							textcolor(10);
							cout << "\n\t\t\tCam on quy khach da su dung dich vu, hen gap lai. \n";
							textcolor(7);
							break;
						}
					case 3:
						system("cls");
						//Chuyen tien
						chuyentien(L,q);
						textcolor(9);
						cout << "\n\n\t\tNhap \"";textcolor(10); cout << "YES"; textcolor(9); cout << "\" de quay lai Menu. Nhap \""; textcolor(4); cout << "NO"; textcolor(9); cout << "\" de thoat: "; textcolor(7);
					rewind(stdin); getline(cin, sLuaChon);
						if(sLuaChon == "yes" || sLuaChon == "YES")
						{
							system("cls");
							goto cc;
						}
						else 
						{
							textcolor(10);
							cout << "\n\t\t\tCam on quy khach da su dung dich vu, hen gap lai. \n";
							textcolor(7);
							break;
						}
					
					case 4:
						system("cls");
						//Lich su giao dich
						docLichSuGiaoDich(q);
						textcolor(9);
						cout << "\n\n\t\tNhap \"";textcolor(10); cout << "YES"; textcolor(9); cout << "\" de quay lai Menu. Nhap \""; textcolor(4); cout << "NO"; textcolor(9); cout << "\" de thoat: "; textcolor(7);
						rewind(stdin); getline(cin, sLuaChon);
						if(sLuaChon == "yes" || sLuaChon == "YES")
						{
							system("cls");
							goto cc;
						}
						else 
						{
							textcolor(10);
							cout << "\n\t\t\tCam on quy khach da su dung dich vu, hen gap lai. \n";
							textcolor(7);
							break;
						}
					case 5:
						system("cls");
						//Doi Mat Khau
						doiMatKhau(L, q);
						break;
					case 6:
						//Thoat khoi giao dich
						textcolor(10);
						cout << "\n\t\t\tCam on quy khach da su dung dich vu, hen gap lai. \n";
						textcolor(7);
						break;
					}
				}
			}
			nDem++;
			if (nDem == 3)
			{
				system("cls");
				thongBao("LOGIN");
				textcolor(4);
				cout << "\t\t\tTai khoan ban da bi khoa !!! Vui Long Lien He: 0988.2.33.77 !!!\a\n\n";
				textcolor(7);
				i += 3;
				for(Node * f = L.pHead; f != NULL; f = f->pNext)
				{
					if(sUsername == f->nData.sUser)
					{
						f->nData.sPass = "locked";
						ghiKH(L);
						Node * e = L.pHead;
						ghiLSGD(L, f, "LOCKED", 0, e, 0);
						break;
					}
				}
			}
			else if (i < 3)
			{

				system("cls");
				thongBao("LOGIN");
				textcolor(4);
				cout << "\t\t\tTai khoan hoac mat khau khong dung.\a Con " << nLan-- << " lan dang nhap \n\n";
				textcolor(7);
				i++;
			}
		}
	}
}

//2.Rut tien:
void rutTien(List L, Node * q)
{
	int nNhapTienRut = 0;
	int nN = 0;
	system("cls");
	do {
		thongBao("RUTTIEN");
		thongBao("MENURUTTIEN"); textcolor(3);
		cout << "\n\t\t\t\tSo tien muon rut: "; textcolor(10);
		cin >> nN;
	} while (nN < 1 || nN > 6);
	switch (nN)
	{
	case 1:
		nNhapTienRut = 50000;
		break;
	case 2:
		nNhapTienRut = 100000;
		break;
	case 3:
		nNhapTienRut = 200000;
		break;
	case 4:
		nNhapTienRut = 500000;
		break;
	case 5:
		nNhapTienRut = 1000000;
		break;
	case 6:
		do {
		dd:
			system("cls");
			thongBao("RUTTIEN");
			textcolor(4);
			cout << "\tGioi han giao dich tu 50.000vnd den 50.000.000vnd\n";
			textcolor(10);
			cout << "\t\t\tNhap so tien can rut: ";
			textcolor(7);
			cin >> nNhapTienRut;
		} while (nNhapTienRut < 50000 || nNhapTienRut > 50000000);
		break;
	}
	if (nNhapTienRut % 50000 == 0)
	{
		double fSoDuKhaDung = 0;
		fSoDuKhaDung = q->nData.fSoDu - 50000;
		if (nNhapTienRut > fSoDuKhaDung)
		{
			textcolor(4);
			cout << "\t\tSo du trong tai khoan khong du de thuc hien giao dich.\n";
			textcolor(7);
		}
		else
		{
			system("cls");
			thongBao("RUTTIEN");
			textcolor(10);
			cout << "\t\t\t   Thong Tin Rut Tien\n";
			textcolor(3);
			cout << "\t\tSTK: " << q->nData.sSTK << endl;
			cout << "\t\tKhach Hang: " << q->nData.sHoTen << endl;
			cout << "\t\tSo Giao Dich: " << nNhapTienRut << " " << q->nData.sLoaiTien << endl;
			cout << "\t\tPhi Giao Dich: " << nPhiGiaoDich(nNhapTienRut, "RUTTIEN") - nPhiGiaoDich(nNhapTienRut, "RUTTIEN") / 11 << " " << q->nData.sLoaiTien << "   -   THUE: " << nPhiGiaoDich(nNhapTienRut, "RUTTIEN") / 11 << " " << q->nData.sLoaiTien << endl;
			cout << "\t\tSo Du Hien Tai: " << q->nData.fSoDu << " " << q->nData.sLoaiTien << endl;
			cout << "\t\tSo Du Con Lai: " << q->nData.fSoDu - (float)nNhapTienRut - (float)nPhiGiaoDich(nNhapTienRut, "RUTTIEN") << " " << q->nData.sLoaiTien << endl;

				q->nData.fSoDu = q->nData.fSoDu - nNhapTienRut - nPhiGiaoDich(nNhapTienRut, "RUTTIEN");
				textcolor(10);
				cout << "\n\t\tBan da rut thanh cong: " << nNhapTienRut << " " << q->nData.sLoaiTien << endl;
				cout << "\t\tSo du con lai: " << q->nData.fSoDu << " " << q->nData.sLoaiTien << endl;
				textcolor(7);
				Node * g = L.pHead;
				//In hoa don rut tien
				string ktra = "";
				textcolor(9);
				cout << "\n\t\tNhap \""; textcolor(10); cout << "YES"; textcolor(9); cout << "\" de in hoa don. Nhap \""; textcolor(4); cout << "NO"; textcolor(9); cout << "\" de thoat: "; textcolor(7);
				rewind(stdin);
				getline(cin, ktra);
				if (ktra == "YES" || ktra == "yes")
				{
					int nPGD = nPhiGiaoDich(nNhapTienRut, "RUTTIEN");
					nPGD += 550;
					inHoaDon(L, q, nNhapTienRut, nPhiGiaoDich(nNhapTienRut, "RUTTIEN"), g, "RUTTIEN");
					ghiKH(L);
					ghiLSGD(L, q, "RUTTIEN", nNhapTienRut, g, nPGD);
				}
				else
				{
					textcolor(10);
					cout << "\t\t\t\tBan khong in hoa don !";
					textcolor(7);
					ghiKH(L);
					ghiLSGD(L, q, "RUTTIEN", nNhapTienRut, g, nPhiGiaoDich(nNhapTienRut, "RUTTIEN"));
				}
			}

		
	}
	else
	{
		cout << "\a";
		goto dd;
	}
}

//3.Chuc nang chuyen tien:
void chuyentien(List L, Node * q)
{
	int flag = 0;
	int i = 0;
	string sNhapSTKChuyen = " ";
	system("cls");
	thongBao("CHUYENTIEN");
	cout << "\t\tLuu y: Nhap ";
	textcolor(4);
	cout << "ESC";
	textcolor(7);
	cout << " de thoat khoi chuong trinh\n" << endl;
	while (flag == 0)
	{
		textcolor(10);
		cout << "\t\tNhap so tai khoan can chuyen tien: ";textcolor(7);
		rewind(stdin);
		label:getline(cin, sNhapSTKChuyen);
		if (sNhapSTKChuyen == "")
		{
			goto label;
		}
		if (sNhapSTKChuyen == q->nData.sSTK)
		{
			textcolor(4);
			cout << "\t\t\tKhong the chuyen tien cho chinh minh !!!\n";
			textcolor(7);
		}
		else if (sNhapSTKChuyen == "ESC" || sNhapSTKChuyen == "esc")
		{
			flag = 5;
			textcolor(10);
			cout << "\t\t\tCam on quy khach da su dung dinh vu\n";
			textcolor(7);
		}
		else
		{
			for(Node * t = L.pHead; t != NULL; t = t->pNext)
			{
				if(sNhapSTKChuyen == t->nData.sSTK)
				{
					flag = 5;
					int nNhapTienChuyen = 0;
					do {
						gg:
						system("cls");
						thongBao("CHUYENTIEN");
						textcolor(4);
						cout << "\t\tSo tien nhap vao phai la boi cua 50.000vnd.\n\t\tGioi han giao dich tu 200.000vnd den 50.000.000vnd\n";
						textcolor(10);
						cout << "\n\t\t\tNhap so tien can chuyen: ";
						textcolor(7);
						cin >> nNhapTienChuyen;
						system("cls");
						if (nNhapTienChuyen % 50000 != 0)
						{
							goto gg;
						}

					} while(nNhapTienChuyen < 200000 || nNhapTienChuyen > 50000000);
					double fSoDuKhaDung = 0.0;
					fSoDuKhaDung = q->nData.fSoDu - 50000;
					if (nNhapTienChuyen >= 200000)
					{
						if (nNhapTienChuyen <= fSoDuKhaDung)
						{
							system("cls");
							thongBao("CHUYENTIEN");
							textcolor(14);
							cout << "\t\t\t  Xac Nhan Chuyen Tien\n";
							textcolor(12);
							cout << "\t\tChuyen Tien Den STK: " << t->nData.sSTK << endl;
							cout << "\t\tTen Nguoi Nhan: " << t->nData.sHoTen << endl;
							cout << "\t\tSo Tien Chuyen: " << nNhapTienChuyen << " " << t->nData.sLoaiTien << endl;
							cout << "\t\tPhi Giao Dich: " << nPhiGiaoDich(nNhapTienChuyen, "CHUYENTIEN") - nPhiGiaoDich(nNhapTienChuyen, "CHUYENTIEN")/11 << " " << q->nData.sLoaiTien << "   -   THUE: " << nPhiGiaoDich(nNhapTienChuyen, "CHUYENTIEN")/11 << " " << q->nData.sLoaiTien << endl;
							cout << "\t\tSo Du Hien Tai: " << q->nData.fSoDu << " " << t->nData.sLoaiTien << endl;
							cout << "\t\tSo Du Con Lai: " << q->nData.fSoDu - (float)nNhapTienChuyen - nPhiGiaoDich(nNhapTienChuyen, "CHUYENTIEN") << " " << t->nData.sLoaiTien << endl;
							
								q->nData.fSoDu = q->nData.fSoDu - (float)nNhapTienChuyen - nPhiGiaoDich(nNhapTienChuyen, "CHUYENTIEN");
								t->nData.fSoDu = t->nData.fSoDu + nNhapTienChuyen;
								textcolor(10);
								cout << "\t\tChuyen Tien Thanh Cong !!!\n";
								cout << "\t\tSo Du Con Lai: "; 
								cout << q->nData.fSoDu << " " << q->nData.sLoaiTien << endl;textcolor(7);
								ghiKH(L);
								//ghiLSGD(L, q, "CHUYENTIEN", nNhapTienChuyen, t,0);
								
								//In hoa don:
								string ktra = "";
								textcolor(9);
								cout << "\t\tNhap \"";textcolor(10); cout << "YES"; textcolor(9); cout << "\" de in hoa don. Nhap \""; textcolor(4); cout << "NO"; textcolor(9); cout << "\" de thoat: "; textcolor(7);
								rewind(stdin);
								getline(cin, ktra);
								if ( ktra == "YES" || ktra == "yes")
								{
									int nPGD = nPhiGiaoDich(nNhapTienChuyen, "CHUYENTIEN");
									nPGD = nPGD + 550;
									inHoaDon(L, q, nNhapTienChuyen, nPhiGiaoDich(nNhapTienChuyen, "CHUYENTIEN"), t, "CHUYENTIEN");
									ghiKH(L);
									ghiLSGD(L, q, "CHUYENTIEN", nNhapTienChuyen, t, nPGD);
									ghiLSGD(L, t, "NHANTIEN", nNhapTienChuyen, q, 0);
									break;
								}
								else
								{
									textcolor(10);
									cout << "\t\t\t\tBan da chon khong in hoa don !";
									textcolor(7);
									ghiKH(L);
									ghiLSGD(L, q, "CHUYENTIEN", nNhapTienChuyen, t, nPhiGiaoDich(nNhapTienChuyen, "CHUYENTIEN"));
									ghiLSGD(L, t, "NHANTIEN", nNhapTienChuyen, q, 0);
									break;
								}
							
						}
						else if (nNhapTienChuyen > fSoDuKhaDung)
						{
							system("cls");
							thongBao("CHUYENTIEN");
							textcolor(4);
							cout << "\n\t\tSo du trong tai khoan khong du de thuc hien giao dich. Giao dich ket thuc !!!\n";
							textcolor(7);
							break;
						}
					}
				}
				else 
				{
					flag = 0;
				}
			}
			if(flag == 0)
			{
				system("cls");
				thongBao("CHUYENTIEN");
				cout << "\t\t\tLuu y: Nhap ";
				textcolor(4);
				cout << "ESE";
				textcolor(7);
				cout << " de thoat khoi chuong trinh\n" << endl;
				textcolor(4);
				cout << "\t\t\tSo tai khoan khong chinh xac. Vui long nhap lai!\n";
				textcolor(7);	
			}
		}
	}
}

//Đoi mat khau:
void doiMatKhau(List L, Node *t)
{
	int nDem = 0;
	system("cls");
	thongBao("DOIMK");
	string matKhauHienTai = "";
dd:
	textcolor(10);
	cout << "\t\t\tNhap Mat Khau Hien Tai: ";
	textcolor(7);
	matKhauHienTai = maHoaMK(6);
	nDem++;
	if (matKhauHienTai == t->nData.sPass)
	{
		string matKhauMoi = "";
		string nhapLaimk = "";
		textcolor(4);
		cout << "\t\t\tLuu y: mat khau gom 6 chu so\n";
		textcolor(7);
		textcolor(013);
		cout << "\t\t\tNhap mat khau moi: ";
		textcolor(7);
		matKhauMoi = maHoaMK(6);
		textcolor(013);
		cout << "\t\t\tNhap lai mat khau moi: ";
		textcolor(7);
		nhapLaimk = maHoaMK(6);
		if (matKhauMoi == nhapLaimk)
		{
			if (matKhauMoi.length() == 6)
			{
				t->nData.sPass = matKhauMoi;
				ghiKH(L);
				textcolor(11);
				cout << "\t\t\t---------------------------\n";
				textcolor(6);
				cout << "\t\t\tThay doi mat khau thanh cong !!!\n";
				cout << "\t\t\tVui long dang nhap lai !!!\n";
				textcolor(7);
			}
			else
			{
				system("cls");
				thongBao("DOIMK");
				textcolor(4);
				cout << "\t\t\tLuu y: mat khau moi bao gom 6 chu so. Vui long nhap lai\n";
				textcolor(7);
				goto dd;
			}
		}
		else if (matKhauMoi == "ESC" || matKhauMoi == "esc" || nhapLaimk == "ESC" || nhapLaimk == "esc")
		{
			textcolor(10);
			cout << "\t\tBan da chon thoat khoi chuong trinh\n";
			textcolor(7);
		}
		else
		{
			system("cls");
			thongBao("DOIMK");
			textcolor(4);
			cout << "\t\tMat khau khong trung khop vui long nhap lai: \n";
			textcolor(7);
			goto dd;
		}
	}
	else if (matKhauHienTai == "esc" || matKhauHienTai == "ESC")
	{
		textcolor(10);
		cout << "Ban da chon thoat khoi chuong trinh\n";
		textcolor(7);
	}
	else if (nDem == 3)
	{
		system("cls");
		thongBao("DOIMK");
		textcolor(4);
		cout << "\t\tBan nhap sai qua 3 lan, tai khoan nay da bi khoa !!! Vui Long Lien He: 0923.778.128 !!!\a\n\n";
		textcolor(7);
		t->nData.sPass = "locked";
		ghiKH(L);
		Node * p = L.pHead;
		ghiLSGD(L, t, "LOCKED", 0, p, 0);
	}
	else
	{
		system("cls");
		thongBao("DOIMK");
		textcolor(4);
		cout << "\t\tMat khau nhap vao sai, Vui long nhap lai.\n";
		cout << "\t\tNhap ESC de thoat khoi chuong trinh !\n";
		textcolor(7);
		goto dd;
	}
}

//Ghi lai du lieu len file
void ghiKH(List &L)
{
	int nSoLuongKhachHang = nDemSoLuongKhachHang();
	ofstream fout;
	fout.open("input.DAT", ios::out);
	int nDem = 0;
	for (Node * k = L.pHead; k != NULL; k = k->pNext)
	{
		nDem++;
		fout << k->nData.sUser << "," << k->nData.sPass << "," << k->nData.sSTK 
			<< "," << k->nData.sHoTen << "," << k->nData.fSoDu << "," << k->nData.sLoaiTien << "," << k->nData.sChiNhanh;
		if(nDem < nSoLuongKhachHang) 
		{
			fout << endl;
		}
	}
	fout.close();
}

//Doc tu file input 1 khach hang
void nhapKH(ifstream &fin, KhachHang &kH) 
{
		
	getline(fin, kH.sUser, ',');
	getline(fin, kH.sPass, ',');
	getline(fin, kH.sSTK, ',');
	getline(fin, kH.sHoTen, ',');
	fin >> kH.fSoDu;
	fin.ignore(1,',');
	getline(fin, kH.sLoaiTien, ',');
	getline(fin, kH.sChiNhanh);
	fin.ignore(0,'\n');
	
}
//Doc tu file input toan bo khach hang
void nhapDSKH(ifstream &fin, List &L) 
{
	while(!fin.eof() == true)  //End Of File : chỉ sự kết thúc việc đọc của 1 file
	{
		KhachHang kH;
		nhapKH(fin, kH); 
		Node * p = createNode(kH); 
		addTail(L, kH); 
	}
	fin.close();
}

//Xuat kiem tra- toan bo khach hang co trong danh sach:
void xuatKH(KhachHang kh)
{
	cout << "\nUser: " << kh.sUser;
	cout << "\nPass: " << kh.sPass;
	cout << "\nSTK: " << kh.sSTK;
	cout << "\nTen: " << kh.sHoTen;
	cout << "\nTien: " << kh.fSoDu << " " << kh.sLoaiTien;
	cout << "\nChi Nhanh: " << kh.sChiNhanh << endl;
}
void xuatDSKH(List L)
{
	int nDem = 1;
	for (Node * k = L.pHead; k != NULL; k = k->pNext)
	{
		cout << "\n\t\t\tKhach Hang Thu " << nDem++;
		xuatKH(k->nData);
	}
}

//Them vao cuoi DS:
void addTail(List &L, KhachHang kH) 
{
	Node *pNew = createNode(kH);
	if (L.pHead == NULL) //Danh sach rong
	{
		L.pHead = L.pTail = pNew;
		return;
	}
	else
	{
		L.pTail->pNext = pNew; 
		L.pTail = pNew; 
	}
}
//Thong bao
void thongBao(string sVien)
{
	if (sVien == "LOGIN")
	{
		textcolor(6);
		cout << "\t\t\t\t+----------------------+" << endl;
		cout << "\t\t\t\t+                      +" << endl;
		cout << "\t\t\t\t+  ";
		textcolor(9);
		cout << "DANG NHAP HE THONG"; textcolor(6);  
		cout <<"  +" << endl;
		cout << "\t\t\t\t+                      +" << endl;
		cout << "\t\t\t\t+----------------------+" << endl;
		textcolor(7);
	}
	else
	{
		if (sVien == "MENU")
		{
			cout << endl;
			textcolor(9);
			cout << "*******************************************************************************" << endl;
			cout << endl;
			textcolor(14);
			cout << "\t\t\t  CHON PHUONG AN DE THUC HIEN"; textcolor(6);  
			cout << endl;
			cout <<"\t\t\t\t" << endl;
			cout << endl;
			textcolor(6);
			cout << "\t  ";
			textcolor(12);
			cout << "   1. Thong Tin Tai Khoan\t\t2. Rut Tien"; textcolor(6);
			cout  << endl;
			cout << endl;
			textcolor(6);
			cout << "\t  ";
			textcolor(12);
			cout << "   3. Chuyen Tien \t\t\t4. Lich su giao dich"; textcolor(6);
			cout  << endl;
			cout << endl;
			textcolor(6);
			cout << "\t  ";
			textcolor(12);
			cout << "   5. Doi Mat Khau \t\t\t6. Thoat giao dich            \t"; textcolor(9);
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "*******************************************************************************" << endl;
			textcolor(7);		
		}
		else if (sVien == "RUTTIEN")
		{
			textcolor(11);
			cout << "\t\t\t  *************************" << endl;
			cout << "\t\t\t  *  ";
			textcolor(4);
			cout << "\t  RUT TIEN\t"; textcolor(11);  
			cout << "  *" << endl;
			cout << "\t\t\t  *************************" << endl;
			textcolor(7);
		}
		else if (sVien == "DOIMK")
		{
			textcolor(3);
			cout << "\t\t\t\t***************************" << endl;
			cout << "\t\t\t\t*  ";
			textcolor(13);
			cout << "\tDOI MAT KHAU\t"; textcolor(3);  
			cout <<"  *" << endl;
			cout << "\t\t\t\t***************************" << endl;
			textcolor(7);
		}
		else if (sVien == "CHUYENTIEN") {
			textcolor(6);
			cout << "\t\t\t**************************" << endl;
			cout << "\t\t\t*  ";
			textcolor(10);
			cout << "\tCHUYEN TIEN\t"; textcolor(6);  
			cout <<" *" << endl;
			cout << "\t\t\t**************************" << endl;
			textcolor(7);
		}
		else if (sVien == "MENURUTTIEN")
		{ 
			textcolor(10);
			cout << "\t\t\tVUI LONG CHON SO TIEN CAN RUT\n";
			textcolor(9);
			cout << "   "; textcolor(13); cout << "1"; textcolor(9); cout << "   \<="; textcolor(4); cout << "\   50.000 VND           \t\t       100.000 VND     "; textcolor(9); cout << "=>"; textcolor(13); cout << "   2" << endl; textcolor(10);

			cout << endl; textcolor(9);

			cout << "   "; textcolor(13); cout << "3"; textcolor(9); cout << "   \<="; textcolor(4); cout << "\   200.000 VND          \t\t       500.000 VND     "; textcolor(9); cout << "=>"; textcolor(13); cout << "   4" << endl; textcolor(10);


			cout << endl; textcolor(9);

			cout << "   "; textcolor(13); cout << "5"; textcolor(9); cout << "   \<="; textcolor(4); cout << "\   1.000.000 VND         \t\t       Nhap So Khac    "; textcolor(9); cout << "=>"; textcolor(13); cout << "   6" << endl; textcolor(10);

			cout << " |/----------------------------/ \t\t \\---------------------------\\|" << endl; textcolor(7);
		}
		
	}
}

//Ma hoa mat khau:
string maHoaMK(unsigned int maxLength)
{
	string pw = "";
	for (char c; (c = _getch()); )
	{
		if (c == '\n' || c == '\r') { // \n là phím phím enter + \r là Nhảy về đầu hàng, không xuống hàng
			cout << "\n";
			break;
		} else if (c == '\b') { //phím backspace
			cout << "\b \b";
			if (!pw.empty()) 
				pw.erase(pw.size()-1);
		} else if (c == -32) { //phím mũi tên
			_getch(); //bỏ qua kí tự tiếp theo (hướng mũi tên)
		} else if (isprint(c) && pw.size() < maxLength) { //isprint tức là chỉ nhận những ký tự in ra được (có tính khoảng trắng)
			cout << '*';
			pw += c;
		}
	}
	return pw;
}

//Thong tin tai khoan:
void thongTinTK(List L, Node *q) 
{
	textcolor(6);
	cout << "   \t\t\t*******************************" << endl;
	cout << "   \t\t\t*  ";
	textcolor(10);
	cout << "   THONG TIN KHACH HANG "; textcolor(6);  
	cout <<"   *" << endl;
	cout << "   \t\t\t*******************************\n\n" << endl;

	textcolor(3);
	cout << "\t\t<----------------------------------------------->" << endl;
	cout << "\t\t\t  ";
	textcolor(12);
	cout << "\n";
	cout << "\t\t\tHo va Ten: " << q->nData.sHoTen << endl;
	cout << "\t\t\tSo Tai Khoan: " << q->nData.sSTK << endl;
	cout << "\t\t\tSo Du Hien Tai: " << q->nData.fSoDu << " " << q->nData.sLoaiTien << endl;
	cout << "\t\t\tChi Nhanh: " << q->nData.sChiNhanh << endl;
	textcolor(3);
	cout << "" << endl;
	cout << "\t\t<----------------------------------------------->" << endl;
	
}

//Ghi lai lich su giao dich:
void ghiLSGD(List L, Node* q, string sChucNang, int nTienTru, Node* g, int nPhiGD)
{
	time_t baygio = time(0);
	tm *t = localtime(&baygio);
	ofstream fout;
	fout.open( q->nData.sSTK + ".dat", ios::app);
	if(sChucNang == "CHUYENTIEN")
	{	
		fout << "\n" << kiemTraTime("hh", q) << t->tm_hour << ":" << kiemTraTime("m", q) << t->tm_min << ":" << kiemTraTime("ss", q) << t->tm_sec << setw(3) << kiemTraTime("dd", q) << t->tm_mday << "/" << kiemTraTime("mm", q) << 1+t->tm_mon << "/" << 1900+t->tm_year  << setw(7) << nTienTru << q->nData.sLoaiTien << kiemTraTime("100", q) << setw(10) << q->nData.fSoDu << q->nData.sLoaiTien << setw(7) << nPhiGD << setw(10) << "Chuyen" << setw(17) << g->nData.sSTK << setw(18) << g->nData.sHoTen << setw(10) << maGiaodich();
	}
	else if (sChucNang == "RUTTIEN")
	{
		fout << "\n" << kiemTraTime("hh", q) << t->tm_hour << ":" << kiemTraTime("m", q) << t->tm_min << ":" << kiemTraTime("ss", q) << t->tm_sec << setw(3) << kiemTraTime("dd", q) << t->tm_mday << "/" << kiemTraTime("mm", q) << 1+t->tm_mon << "/" << 1900+t->tm_year  << setw(7) << nTienTru << q->nData.sLoaiTien << kiemTraTime("100", q) << setw(10) << q->nData.fSoDu << q->nData.sLoaiTien << setw(7) << nPhiGD << setw(10) << "Rut" << setw(12) << "N/A" << setw(15) << "N/A" << setw(15) << maGiaodich();
	}
	else if (sChucNang == "NHANTIEN")
	{
		fout << "\n" << kiemTraTime("hh", q) << t->tm_hour << ":" << kiemTraTime("m", q) << t->tm_min << ":" << kiemTraTime("ss", q) << t->tm_sec << setw(3) << kiemTraTime("dd", q) << t->tm_mday << "/" << kiemTraTime("mm", q) << 1+t->tm_mon << "/" << 1900+t->tm_year  << setw(7) << nTienTru << g->nData.sLoaiTien << kiemTraTime("100", q) << setw(10) << q->nData.fSoDu << q->nData.sLoaiTien << setw(7) << "0" << setw(10) << "Nhan" << setw(17) << g->nData.sSTK << setw(18) << g->nData.sHoTen << setw(10) << maGiaodich();
	}
	else if (sChucNang == "LOCKED")
	{
		fout << "\n" << kiemTraTime("hh", q) << t->tm_hour << ":" << kiemTraTime("m", q) << t->tm_min << ":" << kiemTraTime("ss", q) << t->tm_sec << setw(3) << kiemTraTime("dd", q) << t->tm_mday << "/" << kiemTraTime("mm", q) << 1+t->tm_mon << "/" << 1900+t->tm_year  << setw(7) << "0" << q->nData.sLoaiTien << setw(11) << q->nData.fSoDu << q->nData.sLoaiTien << setw(6) << "0" << setw(11) << "lock" << setw(11) << "N/A" << setw(15) << "N/A" << setw(18) << maGiaodich();
	}
	fout.close();
}

//Xuat lich su giao dich ra man hinh:
void docLichSuGiaoDich(Node * q)
{
	string a = "";
	ifstream fin; 
	fin.open( q->nData.sSTK + ".dat");
	cout << "		          =================>>>LICH SU GIAO DICH<<<=================\n\n";

cout << "hh/mm/ss    Dd/mm/yy    Convert    Wallet    Tran-Fee    Type    Account number    F-L name    Trading code\n";
	while(!fin.eof())
	{
		getline(fin, a, '\n');
		cout << a << endl;
		Sleep(30);
	}
	fin.close();
	cout << "\t\t___________________________________________________________________________\n";
}

//In hoa don:
void inHoaDon(List L, Node * q, int nTienRut, int PhiGD, Node * g, string sForm)
{
	time_t now = time('\00');
	tm *t = localtime(&now);
	if (sForm == "RUTTIEN")
	{
		textcolor(7);
		cout << "\n\n\t\t/----------------------------------------------------\\\n";
		cout << "\t\t| BIDV - Ngan Hang TMCP Dau Tu Va Phat Trien Viet Nam |\n";
		cout << "\t\t|-----------------------------------------------------|\n";
		cout << "\t\t|\t\t\t\t\t\t      |\n";
		cout << "\t\t|\t\t    RUT TIEN MAT\t\t      |\n";
		cout << "\t\t|Ngay\t\t\tGio\t\t       May ATM|\n";
		cout << "\t\t|"<< t->tm_mday << "/" << 1+t->tm_mon << "/" << 1900+t->tm_year << "\t\t" << t->tm_hour << ":" << t->tm_min << "\t\t\t" << sMaATM << "|\n";
		cout << "\t\t|\t\t\t\t\t\t      |\n";
		cout << "\t\t|So tai khoan:  "<< q->nData.sSTK  <<"\t\t\t      |\n";
		cout << "\t\t|So tien rut:   "<< nTienRut << " " << q->nData.sLoaiTien << "\t\t\t      |\n";
		q->nData.fSoDu = q->nData.fSoDu - 550;
		cout << "\t\t|So du tai khoan: " << q->nData.fSoDu << " " << q->nData.sLoaiTien << "\t\t      |\n";
		cout << "\t\t|So giao dich: " << maGiaodich() << "\t\t\t\t      |\n";
		cout << "\t\t|\t\t\t\t\t\t      |\n";
		cout << "\t\t|Phi: " << PhiGD - (PhiGD/11) <<" VND\t\t\tVAT: " << PhiGD/11 << " VND\t      |\n";
		cout << "\t\t|Phi in hoa don: 500 VND\t\t\t      |\n";
		cout << "\t\t|VAT in hoa don: 50 VND \t\t\t      |\n";
		cout << "\t\t|-----------------------------------------------------|\n";
		cout << "\t\t| \tDien thoai ho tro 24/24: 09888.2.33.77 \t      |\n";
		cout << "\t\t\\----------------------------------------------------/\n";
		textcolor(7);
	}
	else if (sForm == "CHUYENTIEN")
	{
		textcolor(7);
		cout << "\n\n\t\t/-----------------------------------------------------\\\n";
		cout << "\t\t BIDV - Ngan Hang TMCP Dau Tu Va Phat Trien Viet Nam \n";
		cout << "\t\t-----------------------------------------------------\n";
		cout << "\t\t\t\t\t\t\t\t  \n";
		cout << "\t\t\t\t  CHUYEN TIEN TRONG NUOC\t \n";
		cout << "\t\tNgay\t\t\tGio\t\t       May ATM\n";
		cout << "\t\t"<< t->tm_mday << "/" << 1+t->tm_mon << "/" << 1900+t->tm_year << "\t\t" << t->tm_hour << ":" << t->tm_min << "\t\t\t" << sMaATM << "\n";
		cout << "\t\t\t\t\t\t\t\t  \n";
		cout << "\t\tSo tai khoan:  "<< q->nData.sSTK  <<"\t\t\t \n";
		cout << "\t\tSo tien chuyen:   "<< nTienRut << " " << q->nData.sLoaiTien << "\t\t\t \n";
		q->nData.fSoDu = q->nData.fSoDu - 550;
		cout << "\t\tSo du tai khoan: " << q->nData.fSoDu << " " << q->nData.sLoaiTien << "\t\t \n";
		cout << "\t\tSo giao dich: " << maGiaodich() << "\t\t\t\t \n";
		cout << "\t\tChuyen den so tai khoan: " << g->nData.sSTK << "\t      \n";
		cout << "\t\t\t\t\t\t\t\t  \n";
		cout << "\t\tPhi: " << PhiGD - (PhiGD/11) <<" VND\t\t\tVAT: " << PhiGD/11 << " VND\t \n";
		cout << "\t\tPhi in hoa don: 500 VND\t\t\t  \n";
		cout << "\t\tVAT in hoa don: 50 VND \t\t\t  \n";
		cout << "\t\t-----------------------------------------------------\n";
		cout << "\t\t \tDien thoai ho tro 24/24: 09888.2.33.77 \t      \n";
		cout << "\t\t\\-----------------------------------------------------/\n";
		textcolor(7);
	}
		
	
}

//Ma giao dich:
int maGiaodich()
{
	int nMaGiaoDich = 0;
	ifstream fin;
	fin.open("IDgiaodich.dat");
	fin >> nMaGiaoDich;
	fin.close();
	ofstream fout;
	fout.open("IDgiaodich.dat");
	nMaGiaoDich = nMaGiaoDich + 1;
	fout << nMaGiaoDich;
	fout.close();
	return nMaGiaoDich;
}

//Phi giao dich:
int nPhiGiaoDich(int nTienNhap, string sForm)
{
	if (sForm == "RUTTIEN")
	{
		if (nTienNhap <= 500000)
		{
			return 3300;
		}
		else if (nTienNhap <= 1000000)
		{
			return 5300;
		}
		else if (nTienNhap <= 10000000)
		{
			return 11000;
		}
		return 22000;
	}
	else if (sForm == "CHUYENTIEN")
	{
		if (nTienNhap <= 1000000)
		{
			return 10000;
		}
		else if (nTienNhap <= 5000000)
		{
			return 15000;
		}
		else if (nTienNhap <= 10000000)
		{
			return 25000;
		}
		return 30000;
	}
	return 0;
}

//Kiem tra thoi gian:
string kiemTraTime(string sX, Node * q)
{
	// làm dữ liệu lịch sử giao dịch \\thẳng hàng\\, thật đẹp để xuất ra màn hình
	time_t now = time('\0');
	tm *t = localtime(&now);
	if (sX == "ss")
	{
		if(t->tm_sec < 10)
		{
			return "0";
		}
	}
	if (sX == "mm")
	{
		if((t->tm_min) < 10)
		{
			return "0";
		}
	}
	if(sX == "hh")
	{
		if(t->tm_hour < 10)
		{
			return "0";
		}
	}
	if (sX == "dd")
	{
		if (t->tm_mday < 10)
		{
			return "0";
		}
	}
	if (sX == "mm")
	{
		if (t->tm_mon + 1 < 10)
		{
			return "0";
		}
	}
	if (sX == "100")
	{
		if (q->nData.fSoDu < 100000)
		{
			return " ";
		}
	}
	return "";
}

void textcolor(int color)
{
	HANDLE hC;
	hC = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hC, color);
}
int nDemSoLuongKhachHang()
{

	int nDem = 0;
	string s = "";
	ifstream fin;
	fin.open("input.dat");
	while(!fin.eof())
	{
		nDem++;
		getline(fin, s, '\n');
	}
	fin.close();
	return nDem;
}
	
