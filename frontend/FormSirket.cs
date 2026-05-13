using System;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace IsIlani
{
    // ═══════════════════════════════════════════════════════════════════════
    //  ŞİRKET GİRİŞ FORMU
    // ═══════════════════════════════════════════════════════════════════════
    public class FormSirketLogin : Form
    {
        private TextBox txtNo;

        public FormSirketLogin()
        {
            Text            = "Şirket Girişi";
            Size            = new Size(380, 200);
            StartPosition   = FormStartPosition.CenterParent;
            FormBorderStyle = FormBorderStyle.FixedDialog;
            MaximizeBox     = false;
            BackColor       = Color.FromArgb(245, 250, 248);
            BuildUI();
        }

        private void BuildUI()
        {
            var lbl = new Label { Text = "Şirket No:", Location = new Point(30, 40),
                                  AutoSize = true, Font = new Font("Segoe UI", 11) };
            txtNo   = new TextBox { Location = new Point(160, 36), Size = new Size(170, 28),
                                    Font = new Font("Segoe UI", 11) };

            var btnGiris = new Button
            {
                Text = "Giriş Yap", Location = new Point(110, 100), Size = new Size(150, 42),
                Font = new Font("Segoe UI", 11, FontStyle.Bold),
                BackColor = Color.FromArgb(34, 140, 100), ForeColor = Color.White,
                FlatStyle = FlatStyle.Flat
            };
            btnGiris.Click += (s, e) =>
            {
                if (!int.TryParse(txtNo.Text.Trim(), out int no))
                {
                    MessageBox.Show("Geçerli bir şirket no giriniz.", "Hata",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning); return;
                }
                if (Backend.sirket_varmi(no) == 0)
                {
                    MessageBox.Show("Bu şirket no ile kayıt bulunamadı.", "Hata",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning); return;
                }
                new FormSirketPanel(no).ShowDialog(this);
            };

            Controls.AddRange(new Control[] { lbl, txtNo, btnGiris });
        }
    }

    // ═══════════════════════════════════════════════════════════════════════
    //  ŞİRKET YÖNETİM PANELİ
    // ═══════════════════════════════════════════════════════════════════════
    public class FormSirketPanel : Form
    {
        private readonly int _sirketNo;
        private TabControl _tab;

        // Şirket bilgi alanları
        private TextBox txtAd, txtAdres, txtTel, txtEmail;

        // İlan yönetimi
        private TextBox txtIlanNo, txtBaslik, txtAciklama, txtPozisyon;
        private ListBox lstIlanlar;
        private Label   lblIlanBilgi;

        // Başvuru görüntüleme
        private ListBox lstBasvuruIlanlar, lstBasvurular;

        public FormSirketPanel(int sirketNo)
        {
            _sirketNo       = sirketNo;
            Text            = "Şirket Paneli";
            Size            = new Size(660, 600);
            StartPosition   = FormStartPosition.CenterParent;
            FormBorderStyle = FormBorderStyle.FixedSingle;
            MaximizeBox     = false;
            BackColor       = Color.FromArgb(245, 250, 248);
            BuildUI();
            PanelYukle();
        }

        private void BuildUI()
        {
            _tab = new TabControl { Dock = DockStyle.Top, Height = 520,
                                    Font = new Font("Segoe UI", 10) };
            _tab.TabPages.Add(TabSirketBilgi());
            _tab.TabPages.Add(TabIlanYonetim());
            _tab.TabPages.Add(TabBasvurular());

            var btnSil = new Button
            {
                Text = "Şirketi Sil", Location = new Point(20, 528),
                Size = new Size(140, 38), BackColor = Color.Crimson, ForeColor = Color.White,
                FlatStyle = FlatStyle.Flat, Font = new Font("Segoe UI", 10)
            };
            btnSil.Click += BtnSirketSil_Click;

            Controls.Add(_tab);
            Controls.Add(btnSil);
        }

        // ── Şirket Bilgileri Sekmesi ──────────────────────────────────────
        private TabPage TabSirketBilgi()
        {
            var p = new TabPage("Şirket Bilgileri"); int y = 20;
            txtAd    = Alan(p, "Şirket Adı:",  ref y);
            txtAdres = Alan(p, "Adres:",       ref y);
            txtTel   = Alan(p, "Telefon:",     ref y);
            txtEmail = Alan(p, "E-posta:",     ref y);

            var btnGunc = Btn("Güncelle", new Point(220, y + 10), Color.FromArgb(34, 140, 100));
            btnGunc.Click += BtnSirketGuncelle_Click;
            p.Controls.Add(btnGunc);
            return p;
        }

        // ── İlan Yönetimi Sekmesi ─────────────────────────────────────────
        private TabPage TabIlanYonetim()
        {
            var p = new TabPage("İlan Yönetimi"); int y = 15;

            txtIlanNo   = Alan(p, "İlan No:",    ref y);
            txtBaslik   = Alan(p, "Başlık:",     ref y);
            txtAciklama = Alan(p, "Açıklama:",   ref y);
            txtPozisyon = Alan(p, "Pozisyon:",   ref y);

            var btnEkle  = Btn("Ekle",    new Point(20,  y + 8), Color.Green);
            var btnGunc  = Btn("Güncelle",new Point(170, y + 8), Color.FromArgb(34,140,100));
            var btnSilI  = Btn("Sil",     new Point(320, y + 8), Color.Crimson);

            btnEkle.Click  += BtnIlanEkle_Click;
            btnGunc.Click  += BtnIlanGuncelle_Click;
            btnSilI.Click  += BtnIlanSil_Click;

            lstIlanlar = new ListBox { Location = new Point(20, y + 62), Size = new Size(590, 130),
                                       Font = new Font("Segoe UI", 9) };
            lstIlanlar.SelectedIndexChanged += LstIlanlar_Changed;

            lblIlanBilgi = new Label { Location = new Point(20, y + 205),
                                       Size = new Size(590, 50),
                                       Font = new Font("Segoe UI", 9),
                                       ForeColor = Color.DarkSlateGray };

            p.Controls.AddRange(new Control[] { btnEkle, btnGunc, btnSilI, lstIlanlar, lblIlanBilgi });
            return p;
        }

        // ── Başvurular Sekmesi ────────────────────────────────────────────
        private TabPage TabBasvurular()
        {
            var p = new TabPage("Başvurular");

            var lbl1 = new Label { Text = "İlanlar:", Location = new Point(20, 20), AutoSize = true };
            lstBasvuruIlanlar = new ListBox { Location = new Point(20, 45), Size = new Size(280, 200),
                                              Font = new Font("Segoe UI", 9) };
            lstBasvuruIlanlar.SelectedIndexChanged += LstBasvuruIlanlar_Changed;

            var lbl2 = new Label { Text = "Başvuranlar (Puana Göre):", Location = new Point(320, 20), AutoSize = true };
            lstBasvurular = new ListBox { Location = new Point(320, 45), Size = new Size(300, 200),
                                          Font = new Font("Segoe UI", 9) };

            p.Controls.AddRange(new Control[] { lbl1, lstBasvuruIlanlar, lbl2, lstBasvurular });
            return p;
        }

        // ── Veri Yükleme ─────────────────────────────────────────────────
        private void PanelYukle()
        {
            var (ad, adres, tel, email) = Backend.SirketBilgiAl(_sirketNo);
            txtAd.Text = ad; txtAdres.Text = adres; txtTel.Text = tel; txtEmail.Text = email;
            IlanlariYukle();
            BasvuruIlanlariYukle();
        }

        private void IlanlariYukle()
        {
            lstIlanlar.Items.Clear();
            int n = Backend.ilan_toplam_sayisi(_sirketNo);
            for (int i = 0; i < n; i++)
            {
                int ilanNo = Backend.ilan_no_listele(_sirketNo, i);
                var (baslik, _, poz) = Backend.IlanBilgiAl(_sirketNo, ilanNo);
                int bsv = Backend.ilan_basvuru_sayisi(_sirketNo, ilanNo);
                lstIlanlar.Items.Add($"[{ilanNo}] {baslik} | {poz} | Başvuru:{bsv}");
            }
        }

        private void BasvuruIlanlariYukle()
        {
            lstBasvuruIlanlar.Items.Clear();
            int n = Backend.ilan_toplam_sayisi(_sirketNo);
            for (int i = 0; i < n; i++)
            {
                int ilanNo = Backend.ilan_no_listele(_sirketNo, i);
                var (baslik, _, _) = Backend.IlanBilgiAl(_sirketNo, ilanNo);
                lstBasvuruIlanlar.Items.Add($"[{ilanNo}] {baslik}");
            }
        }

        private void LstIlanlar_Changed(object sender, EventArgs e)
        {
            if (lstIlanlar.SelectedIndex < 0) return;
            int ilanNo = Backend.ilan_no_listele(_sirketNo, lstIlanlar.SelectedIndex);
            var (baslik, aciklama, poz) = Backend.IlanBilgiAl(_sirketNo, ilanNo);
            lblIlanBilgi.Text = $"Başlık: {baslik}  |  Pozisyon: {poz}\nAçıklama: {aciklama}";
            txtIlanNo.Text   = ilanNo.ToString();
            txtBaslik.Text   = baslik;
            txtAciklama.Text = aciklama;
            txtPozisyon.Text = poz;
        }

        private void LstBasvuruIlanlar_Changed(object sender, EventArgs e)
        {
            lstBasvurular.Items.Clear();
            if (lstBasvuruIlanlar.SelectedIndex < 0) return;
            int ilanNo = Backend.ilan_no_listele(_sirketNo, lstBasvuruIlanlar.SelectedIndex);
            int bsv = Backend.ilan_basvuru_sayisi(_sirketNo, ilanNo);
            for (int i = 0; i < bsv; i++)
            {
                var tc  = new StringBuilder(12);
                var ad  = new StringBuilder(50);
                var soy = new StringBuilder(50);
                Backend.basvuru_bilgi(_sirketNo, ilanNo, i, tc, 12, ad, 50, soy, 50, out float puan);
                lstBasvurular.Items.Add($"{i + 1}. {ad} {soy} | Puan:{puan:F1}");
            }
        }

        // ── Olaylar ──────────────────────────────────────────────────────
        private void BtnSirketGuncelle_Click(object sender, EventArgs e)
        {
            int r = Backend.sirket_guncelle_api(_sirketNo,
                txtAd.Text, txtAdres.Text, txtTel.Text, txtEmail.Text);
            MessageBox.Show(r == 1 ? "Şirket bilgileri güncellendi." : "Güncelleme başarısız.",
                r == 1 ? "Bilgi" : "Hata", MessageBoxButtons.OK,
                r == 1 ? MessageBoxIcon.Information : MessageBoxIcon.Warning);
        }

        private void BtnIlanEkle_Click(object sender, EventArgs e)
        {
            if (!int.TryParse(txtIlanNo.Text, out int ilanNo)) { Msg("Geçerli ilan no giriniz."); return; }
            if (string.IsNullOrWhiteSpace(txtBaslik.Text))     { Msg("Başlık boş olamaz.");       return; }

            int r = Backend.ilan_ekle_api(_sirketNo, ilanNo,
                txtBaslik.Text, txtAciklama.Text, txtPozisyon.Text);

            if      (r ==  1) { Msg("İlan eklendi.", false); IlanlariYukle(); BasvuruIlanlariYukle(); }
            else if (r == -1) Msg("Bu ilan no zaten mevcut.");
            else              Msg("İlan eklenemedi.");
        }

        private void BtnIlanGuncelle_Click(object sender, EventArgs e)
        {
            if (!int.TryParse(txtIlanNo.Text, out int ilanNo)) { Msg("Geçerli ilan no giriniz."); return; }
            int r = Backend.ilan_guncelle_api(_sirketNo, ilanNo,
                txtBaslik.Text, txtAciklama.Text, txtPozisyon.Text);
            MessageBox.Show(r == 1 ? "İlan güncellendi." : "İlan bulunamadı.",
                r == 1 ? "Bilgi" : "Hata", MessageBoxButtons.OK,
                r == 1 ? MessageBoxIcon.Information : MessageBoxIcon.Warning);
            if (r == 1) { IlanlariYukle(); BasvuruIlanlariYukle(); }
        }

        private void BtnIlanSil_Click(object sender, EventArgs e)
        {
            if (!int.TryParse(txtIlanNo.Text, out int ilanNo)) { Msg("Geçerli ilan no giriniz."); return; }
            var onay = MessageBox.Show($"İlan {ilanNo} silinecek. Emin misiniz?",
                "Dikkat", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);
            if (onay == DialogResult.Yes)
            {
                Backend.ilan_sil_api(_sirketNo, ilanNo);
                IlanlariYukle(); BasvuruIlanlariYukle();
            }
        }

        private void BtnSirketSil_Click(object sender, EventArgs e)
        {
            var onay = MessageBox.Show("Şirket ve tüm ilanlar silinecek. Emin misiniz?",
                "Dikkat", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);
            if (onay == DialogResult.Yes)
            {
                Backend.sirket_sil_api(_sirketNo);
                MessageBox.Show("Şirket silindi.", "Bilgi", MessageBoxButtons.OK, MessageBoxIcon.Information);
                Close();
            }
        }

        // ── Yardımcı ─────────────────────────────────────────────────────
        private TextBox Alan(TabPage p, string etiket, ref int y)
        {
            p.Controls.Add(new Label { Text = etiket, Location = new Point(20, y),
                                       AutoSize = true, Font = new Font("Segoe UI", 9) });
            var txt = new TextBox { Location = new Point(200, y - 2), Size = new Size(400, 24),
                                    Font = new Font("Segoe UI", 10) };
            p.Controls.Add(txt); y += 38; return txt;
        }

        private Button Btn(string metin, Point konum, Color renk) =>
            new Button { Text = metin, Location = konum, Size = new Size(130, 36),
                         Font = new Font("Segoe UI", 10), BackColor = renk,
                         ForeColor = Color.White, FlatStyle = FlatStyle.Flat };

        private void Msg(string m, bool hata = true) =>
            MessageBox.Show(m, hata ? "Hata" : "Bilgi", MessageBoxButtons.OK,
                hata ? MessageBoxIcon.Warning : MessageBoxIcon.Information);
    }
}
