using System;
using System.Windows.Forms;
using System.Drawing;

namespace IsIlani
{
    public class FormAna : Form
    {
        public FormAna()
        {
            Text            = "İş İlanı Sistemi - Ana Ekran";
            Size            = new Size(460, 340);
            StartPosition   = FormStartPosition.CenterScreen;
            FormBorderStyle = FormBorderStyle.FixedSingle;
            MaximizeBox     = false;
            BackColor       = Color.FromArgb(240, 244, 250);

            Backend.sistem_baslat();
            Application.ApplicationExit += (s, e) => Backend.sistem_kapat();

            BuildUI();
        }

        private void BuildUI()
        {
            // Başlık
            var lblBaslik = new Label
            {
                Text      = "İş İlanı Sistemi",
                Font      = new Font("Segoe UI", 18, FontStyle.Bold),
                ForeColor = Color.FromArgb(30, 80, 160),
                AutoSize  = true,
                Location  = new Point(120, 30)
            };

            var lblAlt = new Label
            {
                Text      = "Lütfen giriş türünü seçin",
                Font      = new Font("Segoe UI", 10),
                ForeColor = Color.Gray,
                AutoSize  = true,
                Location  = new Point(155, 70)
            };

            // İş Arayan Butonu
            var btnIsArayan = Buton("👤  İş Arayan Girişi", new Point(80, 120), Color.FromArgb(52, 120, 200));
            btnIsArayan.Click += (s, e) => new FormIsArayanLogin().ShowDialog(this);

            // Şirket Butonu
            var btnSirket = Buton("🏢  Şirket Girişi", new Point(80, 185), Color.FromArgb(34, 140, 100));
            btnSirket.Click += (s, e) => new FormSirketLogin().ShowDialog(this);

            // Admin / Kayıt Butonu
            var btnKayit = Buton("📋  Kayıt İşlemleri", new Point(80, 250), Color.FromArgb(160, 80, 30));
            btnKayit.Click += (s, e) => new FormKayit().ShowDialog(this);

            Controls.AddRange(new Control[] { lblBaslik, lblAlt, btnIsArayan, btnSirket, btnKayit });
        }

        private Button Buton(string metin, Point konum, Color renk)
        {
            return new Button
            {
                Text      = metin,
                Location  = konum,
                Size      = new Size(300, 48),
                Font      = new Font("Segoe UI", 11),
                ForeColor = Color.White,
                BackColor = renk,
                FlatStyle = FlatStyle.Flat,
                Cursor    = Cursors.Hand
            };
        }
    }
}
