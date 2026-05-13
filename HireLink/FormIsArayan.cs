using System;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace IsIlani
{
    // ═══════════════════════════════════════════════════════════════════════
    //  GİRİŞ FORMU
    // ═══════════════════════════════════════════════════════════════════════
    public class FormIsArayanLogin : Form
    {
        private TextBox txtTC;

        public FormIsArayanLogin()
        {
            Text            = "İş Arayan Girişi";
            Size            = new Size(380, 200);
            StartPosition   = FormStartPosition.CenterParent;
            FormBorderStyle = FormBorderStyle.FixedDialog;
            MaximizeBox     = false;
            BackColor       = Color.FromArgb(245, 248, 255);
            BuildUI();
        }

        private void BuildUI()
        {
            var lbl = new Label { Text = "TC Kimlik No:", Location = new Point(30, 40),
                                  AutoSize = true, Font = new Font("Segoe UI", 11) };
            txtTC   = new TextBox { Location = new Point(160, 36), Size = new Size(170, 28),
                                    Font = new Font("Segoe UI", 11), MaxLength = 11 };

            var btnGiris = new Button
            {
                Text = "Giriş Yap", Location = new Point(110, 100),
                Size = new Size(150, 42), Font = new Font("Segoe UI", 11, FontStyle.Bold),
                BackColor = Color.FromArgb(52, 120, 200), ForeColor = Color.White,
                FlatStyle = FlatStyle.Flat
            };
            btnGiris.Click += (s, e) =>
            {
                string tc = txtTC.Text.Trim();
                if (tc.Length != 11) { MessageBox.Show("11 haneli TC giriniz.", "Hata",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning); return; }
                if (Backend.ia_varmi(tc) == 0) { MessageBox.Show("Bu TC ile kayıt bulunamadı.", "Hata",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning); return; }
                new FormIsArayanProfil(tc).ShowDialog(this);
            };

            Controls.AddRange(new Control[] { lbl, txtTC, btnGiris });
        }
    }

    // ═══════════════════════════════════════════════════════════════════════
    //  PROFİL FORMU
    // ═══════════════════════════════════════════════════════════════════════
    public class FormIsArayanProfil : Form
    {
        private readonly string _tc;
        private TabControl _tab;

        // Kişisel bilgi alanları
        private TextBox txtAd, txtSoyad, txtAdres, txtTel, txtEmail, txtDogum;

        // Eğitim alanları
        private TextBox txtEOkul, txtEBolum, txtEBas, txtEBit;
        private NumericUpDown numEOrt;
        private ListBox lstEgitim;

        // Deneyim alanları
        private TextBox txtDIsyeri, txtDPoz;
        private NumericUpDown numDYil;
        private ListBox lstDeneyim;

        // Başvuru
        private ListBox lstSirketler, lstIlanlar;
        private Label lblSonuc;

        public FormIsArayanProfil(string tc)
        {
            _tc             = tc;
            Text            = "Profil - " + tc;
            Size            = new Size(620, 580);
            StartPosition   = FormStartPosition.CenterParent;
            FormBorderStyle = FormBorderStyle.FixedSingle;
            MaximizeBox     = false;
            BackColor       = Color.FromArgb(245, 248, 255);
            BuildUI();
            ProfilYukle();
        }

        // ── UI kurulum ───────────────────────────────────────────────────
        private void BuildUI()
        {
            _tab = new TabControl { Dock = DockStyle.Top, Height = 490,
                                    Font = new Font("Segoe UI", 10) };
            _tab.TabPages.Add(TabKisisel());
            _tab.TabPages.Add(TabEgitim());
            _tab.TabPages.Add(TabDeneyim());
            _tab.TabPages.Add(TabBasvuru());

            var btnSil = new Button { Text = "Hesabı Sil", Location = new Point(20, 500),
                Size = new Size(130, 38), BackColor = Color.Crimson, ForeColor = Color.White,
                FlatStyle = FlatStyle.Flat, Font = new Font("Segoe UI", 10) };
            btnSil.Click += BtnSil_Click;

            Controls.Add(_tab);
            Controls.Add(btnSil);
        }

        // ── Kişisel Bilgiler ─────────────────────────────────────────────
        private TabPage TabKisisel()
        {
            var p = new TabPage("Kişisel Bilgiler"); int y = 20;
            txtAd    = Alan(p, "Ad:",            ref y);
            txtSoyad = Alan(p, "Soyad:",         ref y);
            txtAdres = Alan(p, "Adres:",         ref y);
            txtTel   = Alan(p, "Telefon:",       ref y);
            txtEmail = Alan(p, "E-posta:",       ref y);
            txtDogum = Alan(p, "Doğum Tarihi:",  ref y);

            var btnGunc = Btn("Güncelle", new Point(200, y + 10), Color.FromArgb(52, 120, 200));
            btnGunc.Click += BtnGuncelle_Click;
            p.Controls.Add(btnGunc);
            return p;
        }

        // ── Eğitim ──────────────────────────────────────────────────────
        private TabPage TabEgitim()
        {
            var p = new TabPage("Eğitim"); int y = 15;
            txtEOkul  = Alan(p, "Okul:",           ref y);
            txtEBolum = Alan(p, "Bölüm:",          ref y);
            txtEBas   = Alan(p, "Başlama (YYYY):",  ref y);
            txtEBit   = Alan(p, "Bitiş (YYYY):",   ref y);

            p.Controls.Add(new Label { Text = "Ortalama:", Location = new Point(20, y),
                                       AutoSize = true, Font = new Font("Segoe UI", 9) });
            numEOrt = new NumericUpDown { Location = new Point(200, y - 2), Size = new Size(80, 24),
                                          DecimalPlaces = 2, Minimum = 0, Maximum = 4,
                                          Increment = 0.05m, Font = new Font("Segoe UI", 10) };
            p.Controls.Add(numEOrt); y += 38;

            var btnEkle = Btn("Ekle", new Point(20, y), Color.Green);
            var btnSil  = Btn("Seçili Sil", new Point(170, y), Color.Crimson);
            btnEkle.Click += BtnEgitimEkle_Click;
            btnSil.Click  += BtnEgitimSil_Click;

            lstEgitim = new ListBox { Location = new Point(20, y + 55),
                                      Size = new Size(550, 150), Font = new Font("Segoe UI", 9) };
            p.Controls.AddRange(new Control[] { btnEkle, btnSil, lstEgitim });
            return p;
        }

        // ── Deneyim ─────────────────────────────────────────────────────
        private TabPage TabDeneyim()
        {
            var p = new TabPage("Deneyim"); int y = 15;
            txtDIsyeri = Alan(p, "İş Yeri:",    ref y);
            txtDPoz    = Alan(p, "Pozisyon:",   ref y);

            p.Controls.Add(new Label { Text = "Deneyim Yılı:", Location = new Point(20, y),
                                       AutoSize = true, Font = new Font("Segoe UI", 9) });
            numDYil = new NumericUpDown { Location = new Point(200, y - 2), Size = new Size(80, 24),
                                          Minimum = 0, Maximum = 50, Font = new Font("Segoe UI", 10) };
            p.Controls.Add(numDYil); y += 38;

            var btnEkle = Btn("Ekle", new Point(20, y), Color.Green);
            var btnSil  = Btn("Seçili Sil", new Point(170, y), Color.Crimson);
            btnEkle.Click += BtnDeneyimEkle_Click;
            btnSil.Click  += BtnDeneyimSil_Click;

            lstDeneyim = new ListBox { Location = new Point(20, y + 55),
                                       Size = new Size(550, 150), Font = new Font("Segoe UI", 9) };
            p.Controls.AddRange(new Control[] { btnEkle, btnSil, lstDeneyim });
            return p;
        }

        // ── Başvuru ─────────────────────────────────────────────────────
        private TabPage TabBasvuru()
        {
            var p = new TabPage("Başvuru Yap");

            var lbl1 = new Label { Text = "Şirketler:", Location = new Point(20, 20), AutoSize = true };
            lstSirketler = new ListBox { Location = new Point(20, 45), Size = new Size(250, 180),
                                         Font = new Font("Segoe UI", 9) };
            lstSirketler.SelectedIndexChanged += LstSirketler_Changed;

            var lbl2 = new Label { Text = "İlanlar:", Location = new Point(300, 20), AutoSize = true };
            lstIlanlar = new ListBox { Location = new Point(300, 45), Size = new Size(270, 180),
                                       Font = new Font("Segoe UI", 9) };

            var btnBasvur = Btn("Başvur", new Point(200, 240), Color.FromArgb(52, 120, 200));
            btnBasvur.Click += BtnBasvur_Click;

            lblSonuc = new Label { Location = new Point(20, 295), Size = new Size(560, 30),
                                   Font = new Font("Segoe UI", 10, FontStyle.Bold),
                                   ForeColor = Color.DarkGreen };

            p.Controls.AddRange(new Control[] { lbl1, lstSirketler, lbl2, lstIlanlar, btnBasvur, lblSonuc });
            return p;
        }

        // ── Veri Yükleme ─────────────────────────────────────────────────
        private void ProfilYukle()
        {
            var (ad, soyad, adres, tel, email, dogum) = Backend.IaBilgiAl(_tc);
            txtAd.Text = ad; txtSoyad.Text = soyad; txtAdres.Text = adres;
            txtTel.Text = tel; txtEmail.Text = email; txtDogum.Text = dogum;
            EgitimlerYukle();
            DeneyimlerYukle();
            SirketleriYukle();
        }

        private void EgitimlerYukle()
        {
            lstEgitim.Items.Clear();
            int n = Backend.ia_egitim_sayisi(_tc);
            for (int i = 0; i < n; i++)
            {
                var okul  = new StringBuilder(100); var bolum = new StringBuilder(100);
                var bas   = new StringBuilder(20);  var bit   = new StringBuilder(20);
                Backend.ia_egitim_bilgi(_tc, i, okul, 100, bolum, 100, bas, 20, bit, 20, out float ort);
                lstEgitim.Items.Add($"{okul} | {bolum} | {bas}~{bit} | Ort:{ort:F2}");
            }
        }

        private void DeneyimlerYukle()
        {
            lstDeneyim.Items.Clear();
            int n = Backend.ia_deneyim_sayisi(_tc);
            for (int i = 0; i < n; i++)
            {
                var isyeri = new StringBuilder(100); var poz = new StringBuilder(100);
                Backend.ia_deneyim_bilgi(_tc, i, isyeri, 100, poz, 100, out int yil);
                lstDeneyim.Items.Add($"{isyeri} | {poz} | {yil} yıl");
            }
        }

        private void SirketleriYukle()
        {
            lstSirketler.Items.Clear();
            int n = Backend.sirket_toplam_sayisi();
            for (int i = 0; i < n; i++)
            {
                int no = Backend.sirket_no_listele(i);
                var (ad, _, _, _) = Backend.SirketBilgiAl(no);
                lstSirketler.Items.Add($"[{no}] {ad}");
            }
        }

        private void LstSirketler_Changed(object sender, EventArgs e)
        {
            lstIlanlar.Items.Clear();
            if (lstSirketler.SelectedIndex < 0) return;
            int sirketNo = Backend.sirket_no_listele(lstSirketler.SelectedIndex);
            int n = Backend.ilan_toplam_sayisi(sirketNo);
            for (int i = 0; i < n; i++)
            {
                int ilanNo = Backend.ilan_no_listele(sirketNo, i);
                var (baslik, _, poz) = Backend.IlanBilgiAl(sirketNo, ilanNo);
                lstIlanlar.Items.Add($"[{ilanNo}] {baslik} | {poz}");
            }
        }

        // ── Olaylar ──────────────────────────────────────────────────────
        private void BtnGuncelle_Click(object sender, EventArgs e)
        {
            int r = Backend.ia_guncelle(_tc, txtAd.Text, txtSoyad.Text,
                        txtAdres.Text, txtTel.Text, txtEmail.Text, txtDogum.Text);
            MessageBox.Show(r == 1 ? "Bilgiler güncellendi." : "Güncelleme başarısız.",
                r == 1 ? "Bilgi" : "Hata", MessageBoxButtons.OK,
                r == 1 ? MessageBoxIcon.Information : MessageBoxIcon.Warning);
        }

        private void BtnEgitimEkle_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(txtEOkul.Text)) { Msg("Okul adı boş olamaz."); return; }
            Backend.ia_egitim_ekle(_tc, txtEOkul.Text, txtEBolum.Text,
                txtEBas.Text, txtEBit.Text, (float)numEOrt.Value);
            EgitimlerYukle();
            txtEOkul.Clear(); txtEBolum.Clear(); txtEBas.Clear(); txtEBit.Clear();
        }

        private void BtnEgitimSil_Click(object sender, EventArgs e)
        {
            if (lstEgitim.SelectedIndex < 0) { Msg("Silinecek eğitimi seçin."); return; }
            // Seçili satırdan okul|bölüm parse et
            string[] parcalar = lstEgitim.SelectedItem.ToString().Split('|');
            if (parcalar.Length < 2) return;
            Backend.ia_egitim_sil(_tc, parcalar[0].Trim(), parcalar[1].Trim());
            EgitimlerYukle();
        }

        private void BtnDeneyimEkle_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(txtDIsyeri.Text)) { Msg("İş yeri boş olamaz."); return; }
            Backend.ia_deneyim_ekle(_tc, txtDIsyeri.Text, txtDPoz.Text, (int)numDYil.Value);
            DeneyimlerYukle();
            txtDIsyeri.Clear(); txtDPoz.Clear();
        }

        private void BtnDeneyimSil_Click(object sender, EventArgs e)
        {
            if (lstDeneyim.SelectedIndex < 0) { Msg("Silinecek deneyimi seçin."); return; }
            string[] parcalar = lstDeneyim.SelectedItem.ToString().Split('|');
            if (parcalar.Length < 2) return;
            Backend.ia_deneyim_sil(_tc, parcalar[0].Trim(), parcalar[1].Trim());
            DeneyimlerYukle();
        }

        private void BtnBasvur_Click(object sender, EventArgs e)
        {
            if (lstSirketler.SelectedIndex < 0 || lstIlanlar.SelectedIndex < 0)
            {
                lblSonuc.ForeColor = Color.Crimson;
                lblSonuc.Text = "Lütfen şirket ve ilan seçin."; return;
            }
            int sirketNo = Backend.sirket_no_listele(lstSirketler.SelectedIndex);
            int ilanNo   = Backend.ilan_no_listele(sirketNo, lstIlanlar.SelectedIndex);
            int r        = Backend.basvuru_yap(_tc, sirketNo, ilanNo);

            if      (r ==  1) { lblSonuc.ForeColor = Color.DarkGreen; lblSonuc.Text = "Başvurunuz alındı!"; }
            else if (r == -1) { lblSonuc.ForeColor = Color.DarkOrange; lblSonuc.Text = "Bu ilana zaten başvurdunuz."; }
            else              { lblSonuc.ForeColor = Color.Crimson;     lblSonuc.Text = "Başvuru başarısız."; }
        }

        private void BtnSil_Click(object sender, EventArgs e)
        {
            var onay = MessageBox.Show("Hesabınız silinecek. Emin misiniz?",
                "Dikkat", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);
            if (onay == DialogResult.Yes)
            {
                Backend.ia_sil(_tc);
                MessageBox.Show("Hesap silindi.", "Bilgi", MessageBoxButtons.OK, MessageBoxIcon.Information);
                Close();
            }
        }

        // ── Yardımcı ─────────────────────────────────────────────────────
        private TextBox Alan(TabPage p, string etiket, ref int y)
        {
            p.Controls.Add(new Label { Text = etiket, Location = new Point(20, y),
                                       AutoSize = true, Font = new Font("Segoe UI", 9) });
            var txt = new TextBox { Location = new Point(200, y - 2), Size = new Size(350, 24),
                                    Font = new Font("Segoe UI", 10) };
            p.Controls.Add(txt); y += 38; return txt;
        }

        private Button Btn(string metin, Point konum, Color renk) =>
            new Button { Text = metin, Location = konum, Size = new Size(130, 36),
                         Font = new Font("Segoe UI", 10), BackColor = renk,
                         ForeColor = Color.White, FlatStyle = FlatStyle.Flat };

        private void Msg(string m) => MessageBox.Show(m, "Uyarı",
            MessageBoxButtons.OK, MessageBoxIcon.Warning);
    }
}
