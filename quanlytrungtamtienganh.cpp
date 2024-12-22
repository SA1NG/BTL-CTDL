#include<iostream>
#include<string.h>
using namespace std;

//Cau Truc Thong Tin Ca Nhan
struct ThongTinCaNhan;
// Cau Truc Giang Vien
struct GiangVien;
// Cau Truc Nhan Vien
struct NhanVien;
// Cau Truc Hoc Vien
struct HocVien;
// Cau truc Khoa Hoc
struct KhoaHoc;
// Nut Giang Vien
typedef GiangVien* N_GiangVien;
// Nut Hoc Vien
typedef HocVien* N_HocVien;
//Nut Khoa Hoc
typedef KhoaHoc* N_KhoaHoc;
// Danh Sach Giang Vien
typedef N_GiangVien DS_GiangVien;
// Danh Sach Hoc Vien
typedef N_HocVien DS_HocVien;
// Danh Sach Khoa Hoc
typedef N_KhoaHoc DS_KhoaHoc;
// Cau Truc Buoi Hoc
struct BuoiHoc;
// Nut Buoi Hoc;
typedef BuoiHoc* N_BuoiHoc;
// Danh Sach Buoi Hoc
typedef N_BuoiHoc DS_BuoiHoc;

//Cau Truc Thong Tin Ca Nhan
struct ThongTinCaNhan {
    short ma_so;
    string ten;
    short tuoi;
    string cccd;
    string sdt;
    string nghe_nghiep;
    string trinh_do;
};
// Cau Truc Giang Vien
struct GiangVien {
    ThongTinCaNhan tt_gv;
    int luong; // theo 1 hoc vien
    DS_KhoaHoc Ds_kh;
    GiangVien* Next;
};
// Cau Truc Hoc Vien
struct HocVien {
    ThongTinCaNhan tt_hv;
    DS_KhoaHoc Ds_kh;
    HocVien* Next;
};
// Cau Truc Buoi Hoc
struct BuoiHoc {
    float gio;
    short ngay, thang, nam;
    short buoi_so;
    short phong_hoc;
    bool trang_thai;
    BuoiHoc* Next;
};
// Cau truc Khoa Hoc
struct KhoaHoc {
    short ma_so;
    string ten;
    int gia_tien;
    short muc_tieu;
    short trang_thai;
    DS_BuoiHoc Ds_bh;
    N_GiangVien Gv;
    DS_HocVien Ds_hv;
    KhoaHoc* Next;
};

// CAC THAO TAC VOI BUOI HOC
// CAC Thao Tac Tinh Ngay

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
    short thu = (Ngay + (13 * (Thang + 1)) / 5 + (Nam % 100) + (Nam % 100) / 4 + (Nam / 100) / 4 + 5 * (Nam / 100)) % 7;

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
void TaoDanhSachBuoiHoc(DS_BuoiHoc& DSBH, short So_buoi, short Tan_suat){ // Tan Suat Lon La 7
    N_BuoiHoc P = DSBH;
    N_BuoiHoc R = DSBH;
    while(R->Next != NULL) R = R->Next;
    for(int i = Tan_suat + 1; i <= So_buoi;i++){
        //Tao ra 1 Buoi Hoc
        N_BuoiHoc newBh = new BuoiHoc;
        newBh->buoi_so = i;
        newBh->gio = P->gio;
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


// CAC THAO TAC VOI THONG TIN CA NHAN

// Khoi Tao Thong Tin Ca Nhan
ThongTinCaNhan InitTTCN(int Ma_so, string Ten, int Tuoi, int Cccd, string Sdt, string trinh_do ){
    ThongTinCaNhan Cn;
    Cn.ma_so = Ma_so;
    Cn.ten = Ten;
    Cn.tuoi = Tuoi;
    Cn.cccd = Cccd;
    Cn.sdt = Sdt;
    Cn.trinh_do = trinh_do;
    Cn.nghe_nghiep = "";
}


// CAC THAO TAC VOI GIANG VIEN

// Khoi Tao Danh Sach Giang Vien
void initGV(DS_GiangVien& DSGV){
    DSGV = NULL;
}  
// Kiem Tra Danh Sach Giang Vien Rong
bool GVisEmpty(DS_GiangVien& DSGV){
    return (DSGV == NULL);
}
// Tao Ra Mot Nut Giang Vien
N_GiangVien GV(ThongTinCaNhan Tt_gv, int Luong){
    N_GiangVien newGv = new GiangVien;
    newGv->tt_gv = Tt_gv;
    newGv->tt_gv.nghe_nghiep = "Giang Vien Toiec";
    newGv->luong = Luong;
    newGv->Ds_kh = NULL;
    newGv->Next = NULL;
    return newGv;
}
// Them Giang Vien
void insertGV(DS_GiangVien& DSGV, N_GiangVien Gv){
    Gv->Next = DSGV;
    DSGV = Gv;
}
// Tim Kiem Giang Vien Dua Vao Ma So
N_GiangVien findGVbyMaSo(DS_GiangVien& DSGV, int MaSo){
    if(DSGV == NULL) return NULL;
    N_GiangVien P = DSGV;
    while(P != NULL){
        if(MaSo != P->tt_gv.ma_so){
            P = P->Next;
        } else break;
    }
    return P;
}

// Xoa Giang Vien
bool deleteGV(DS_GiangVien& DSGV, N_GiangVien Gv){
    if(DSGV == NULL || Gv == NULL) return false;
    if(DSGV == Gv && Gv->Next == NULL){
        DSGV = NULL;
        delete Gv;
        return true;
    }

    if(DSGV == Gv){
        DSGV = Gv->Next;
        delete Gv;
        return true;
    }

    N_GiangVien P = DSGV;
    while(P->Next != NULL && P->Next != Gv){
        P = P->Next;
    }
    if(P->Next == Gv){
        P->Next = Gv->Next;
        delete Gv;
        return true;
    }
    return false;
}
// Xoa Danh Sach Giang Vien
void deleteAllGV(DS_GiangVien& DSGV){
    while(DSGV != NULL){
        N_GiangVien P = DSGV;
        DSGV = P->Next;
        delete P;
    }
    return;
}
// Them Khoa Hoc Cho Giang Vien
void insertKHtoGV(N_GiangVien Gv, N_KhoaHoc Kh){
    Kh->Next = Gv->Ds_kh;
    Gv->Ds_kh = Kh;
}
// Xoa Khoa Hoc Cua Giang Vien
bool deleteKHinGV(N_GiangVien Gv, N_KhoaHoc Kh){
    N_KhoaHoc newKh = Kh;
    DS_KhoaHoc dskh = Gv->Ds_kh;
    return deleteKh(dskh, newKh);
}
// Tinh So Luong Giang Vien
int SoLuongGV(DS_GiangVien DSGV){
    if(GVisEmpty(DSGV)) return 0;
    return 1 + SoLuongGV(DSGV->Next);
}

// In Danh Sach Giang Vien
void ShowGV(DS_GiangVien DSGV){
    if(GVisEmpty(DSGV)){
        cout << "Hien tai chua co giang vien nao";
        return;
    }
    N_GiangVien P = DSGV;
    int i = 1;
    while(P != NULL){
        cout << i << ". " << P->tt_gv.ma_so << "\t" << P->tt_gv.ten << endl;
        P = P->Next;
        i++;
    }
}
// CAC THAO TAC VOI HOC VIEN

// Khoi Tao Danh Sach Hoc vien
void initHocVien(DS_HocVien& DSHV){
    DSHV = NULL;
}
// Kiem Tra Danh Sach Hoc Vien Rong
bool HVisEmpty(DS_HocVien& DSHV){
    return (DSHV == NULL);
}
// Tao Ra Mot Nut Hoc Vien
N_HocVien HV(int ma_so, string ten, int tuoi, int cccd){
    N_HocVien newHv = new HocVien;
    newHv->tt_hv.ma_so = ma_so;
    newHv->tt_hv.ten = ten;
    newHv->tt_hv.tuoi = tuoi;
    newHv->tt_hv.cccd = cccd;
    newHv->Ds_kh = NULL;
    newHv->Next = NULL;
    return newHv;
}
// Them Hoc vien
void insertHV(DS_HocVien& DSHV, N_HocVien Hv){
    Hv->Next = DSHV;
    DSHV = Hv;
}
// Tim Kiem Hoc Vien Bang Ma So
N_HocVien findHVbyMaSo(DS_HocVien& DSHV, int MaSo){
    if(DSHV == NULL) return NULL;
    N_HocVien P = DSHV;
    while(P != NULL){
        if(MaSo != P->tt_hv.ma_so){
            P = P->Next;
        } else break;
    }
    return P;
}
// Xoa Hoc Vien
bool deleteHV(DS_HocVien& DSHV, N_HocVien Hv){
    if(DSHV == NULL || Hv == NULL) return false;
    if(DSHV == Hv && Hv->Next == NULL){
        DSHV = NULL;
        delete Hv;
        return true;
    }

    if(DSHV == Hv){
        DSHV = Hv->Next;
        delete Hv;
        return true;
    }

    N_HocVien P = DSHV;
    while(P->Next != NULL && P->Next != Hv){
        P = P->Next;
    }
    if(P->Next == Hv){
        P->Next = Hv->Next;
        delete Hv;
        return true;
    }
    return false;
}
// Them Khoa Hoc Cho Hoc Vien
void insertKHtoHV(N_HocVien Hv, N_KhoaHoc Kh){
    Kh->Next = Hv->Ds_kh;
    Hv->Ds_kh = Kh;
}
// Tinh So Luong Cho Hoc Vien
int SoLuongHV(DS_HocVien DSHV){
    if(HVisEmpty(DSHV)) return 0;
    return 1 + SoLuongHV(DSHV->Next);
}
// Hien Thi Danh Sach Hoc Vien
void ShowHV(DS_HocVien DSHV){
    if(HVisEmpty(DSHV)){
        cout << "Hien tai chua co hoc vien nao.";
        return;
    }
    N_HocVien P = DSHV;
    int i = 1;
    while(P != NULL){
        cout << i << ". " << P->tt_hv.ma_so << "\t" << P->tt_hv.ten << endl;
        P = P->Next;
        i++;
    }
}

// CAC THAO TAC VOI KHOA HOC

// Khoi Tao Danh Sach Khoa Hoc
void initKhoaHoc(DS_KhoaHoc& DSKH){
    DSKH = NULL;
}
// Kiem Tra Danh Sach Khoa Hoc Rong
bool KHisEmpty(DS_KhoaHoc& DSKH){
    return (DSKH == NULL);
}
// Tao Ra Mot Nut Khoa Hoc
N_KhoaHoc KH(int Ma_so, string Ten, int Gia_tien, N_GiangVien Gv ){
    N_KhoaHoc Kh = new KhoaHoc;
    Kh->ma_so = Ma_so;
    Kh->ten = Ten;
    Kh->gia_tien = Gia_tien;
    Kh->Gv = Gv;
    Kh->Ds_hv = NULL;
    Kh->Ds_bh = NULL;
    Kh->Next = NULL;
    return Kh;
}
// Them Khoa Hoc
void insertKh(DS_KhoaHoc& DSKH, N_KhoaHoc Kh){
    Kh->Next = DSKH;
    DSKH = Kh;
}
// Tim Kiem Khoa Hoc Bang Ma So
N_KhoaHoc findKhbyMaSo(DS_KhoaHoc& DSKH, int MaSo){
    if(DSKH == NULL) return NULL;
    N_KhoaHoc Kh = DSKH;
    while(Kh != NULL){
        if(MaSo != Kh->ma_so){
            Kh = Kh->Next;
        } else break;
    }
    return Kh;
}
// Xoa Khoa Hoc
bool deleteKh(DS_KhoaHoc& DSKH, N_KhoaHoc Kh){
    if(DSKH == NULL || Kh == NULL) return false;
    if(DSKH == Kh && Kh->Next == NULL){
        DSKH = NULL;
        delete Kh;
        return true;
    }

    if(DSKH == Kh){
        DSKH = Kh->Next;
        delete Kh;
        return true;
    }

    N_KhoaHoc newKh = DSKH;
    while(newKh->Next != NULL && newKh->Next != Kh){
        newKh = newKh->Next;
    }
    if(newKh->Next == Kh){
        newKh->Next = Kh->Next;
        delete Kh;
        return true;
    }
    return false;
}
// Them Hoc Vien Cho Khoa Hoc
void insertHVtoKH(N_KhoaHoc Kh, N_HocVien Hv){
    Hv->Ds_kh->Next = Kh;
    Kh = Hv->Ds_kh;
}
// Tinh So Luong Khoa Hoc
int SoLuongKh(DS_KhoaHoc DSKH){
    if(KHisEmpty(DSKH)) return 0;
    return 1 + SoLuongKh(DSKH->Next);
}
// Tinh So Luong Buoi Hoc Cua Khoa Hoc Trong 1 Thang

//Hien Thi Danh Sach Khoa Hoc
void ShowKH(DS_KhoaHoc DSKH){
    if(KHisEmpty(DSKH)){
        cout << "Hien tai chua co khoa hoc nao.";
        return;
    }
    N_KhoaHoc Kh = DSKH;
    int i = 1;
    while(Kh != NULL){
        cout << i << ". " << Kh->ma_so << "\t" << Kh->ten << endl;
        Kh = Kh->Next;
        i++;
    }
}
