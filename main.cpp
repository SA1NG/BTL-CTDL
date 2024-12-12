#include<iostream>
using namespace std;

// Cau Truc Buoi Hoc
struct BuoiHoc {
    float gio;
    short ngay, thang, nam;
    short buoi_so;
    bool trang_thai;
    short phong_hoc;
    BuoiHoc* Next;
};
typedef struct BuoiHoc* DS_BuoiHoc;
typedef struct BuoiHoc* N_BuoiHoc;
// Ham Kiem Tra Nam Nhuan
bool NamNhuan(short Nam){
    return (Nam % 4 == 0 && Nam % 100 != 0) || (Nam % 400 == 0);
}
// Trả ve So Ngay Trong Thang
short SoNgay(short Thang, short Nam){
    switch (Thang) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return NamNhuan(Nam) ? 29 : 28;
        default: return 0;
    }
}
// Tinh Thu Trong Tuan
short TinhThu(int Ngay, int Thang, int Nam) {
    // Cong Thuc Zeller Congruence
    if (Thang < 3) {
        Thang += 12;
        Nam -= 1;
    }
    short thu = (Ngay + (13 * (Thang + 1)) / 5 + Nam % 100 + Nam % 100 / 4 + Nam / 100 / 4 + 5 * Nam / 100) % 7;

    return thu / 7;
}

// CAC THAO TAC VOI BUOI HOC

// Khoi Tao Danh Sach Buoi Hoc
void initBH(DS_BuoiHoc& DSBH){
    DSBH = NULL;
}
// Kiem Tra Danh Sach Rong
bool BHisEmpty(DS_BuoiHoc& DSBH){
    return (DSBH == NULL);
}
// Tao Ra Nut Buoi Hoc
N_BuoiHoc BH(float Gio, short Ngay, short Thang, short Nam, short Buoi_so, short Phong_hoc){
    // Kiem Tra Thoi Gian Hop Le
    if((Gio > 21 || Gio < 17) && TinhThu(Ngay, Thang, Nam) > 1){
        cout << "Gio Hoc Nen Trong Khoang 17h Den 21h";
        return NULL;
    }
    if(Thang < 1 || Thang > 12){
        cout << "Thang Khong Hop Le";
        return NULL;
    }
    if (Ngay < 1 || Ngay > SoNgay(Thang, Nam)) {
        cout << "Ngay Khong Hop Le" << endl;
        return NULL;
    }
    // Tao Ra Buoi Hoc Dau Tien
    N_BuoiHoc newBh = new BuoiHoc;
    newBh->gio = Gio;
    newBh->ngay = Ngay;
    newBh->thang = Thang;
    newBh->nam = Nam;
    newBh->buoi_so = Buoi_so;
    newBh->trang_thai = 0;
    newBh->phong_hoc = Phong_hoc;
    newBh->Next = NULL;
    return newBh;
}
// Them Buoi Hoc Vao Danh Sach
void insertBH(DS_BuoiHoc& DSBH, N_BuoiHoc Bh){
    if(BHisEmpty(DSBH)){
        Bh->Next = NULL;
        DSBH = Bh;
    } else {
        N_BuoiHoc P = DSBH;
        while(P->Next != NULL) P = P->Next;
        P->Next = Bh;
    }
}

//Tao Danh Sach Buoi Hoc
void TaoDanhSachBuoiHoc(DS_BuoiHoc& DSBH, short So_buoi, short Tan_suat){ // Tan Suat Nho Nhat La 7
    N_BuoiHoc P = DSBH;
    N_BuoiHoc R = DSBH;
    while(R->Next != NULL) R = R->Next;
    for(int i = Tan_suat; i <= So_buoi;i++){
        //Tao ra 1 Buoi Hoc
        N_BuoiHoc newBh = new BuoiHoc;
        newBh->buoi_so = i;
        newBh->phong_hoc = P->phong_hoc;
        newBh->trang_thai = 0;
        newBh->Next = NULL;
        // Tao Thoi Gian Hoc Cho Buoi Moi
        short So_ngay = SoNgay(R->thang, R->nam);
        if (R->ngay + Tan_suat <= So_ngay) {
            newBh->ngay = R->ngay + Tan_suat;
            newBh->thang = R->thang;
            newBh->nam = R->nam;
        } else {
            newBh->ngay = R->ngay + Tan_suat - So_ngay;
            newBh->thang = R->thang + 1;
            if (newBh->thang > 12) {
                newBh->thang = 1;
                newBh->nam = R->nam + 1;
            }
        }
        R->Next = newBh;
        R = R->Next;
        P = P->Next;
    }
}

void show(DS_BuoiHoc Bh) {
    if (Bh == NULL) {
        cout << "rong" << endl;
        return;
    }
    while (Bh != NULL) {
        cout << "Buoi so: " << Bh->buoi_so << endl;
        Bh = Bh->Next;
    }
}

int main(){
    DS_BuoiHoc bh;
    initBH(bh);
    N_BuoiHoc x = BH(19,12,12,2024,1,201);
    insertBH(bh, x);
    N_BuoiHoc y = BH(19,13,12,2024,2,301);
    insertBH(bh, y);
    insertBH(bh, BH(20, 12, 9, 2024, 3, 125));
    show(bh);
}

