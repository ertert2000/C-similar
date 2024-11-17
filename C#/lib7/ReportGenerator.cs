//using iText.Kernel.Pdf;
//using PdfSharp.Drawing;
using PdfSharp.Drawing.Layout;
using iText.Layout.Element;
using iText.Layout;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Controls;
using PdfSharpCore.Pdf;
using PdfSharpCore.Drawing;
using Org.BouncyCastle.Asn1.Pkcs;

namespace lib3_1
{
    class ReportGenerator
    {
        private DataGrid dataGrid;

        public ReportGenerator(DataGrid dataGrid) => this.dataGrid = dataGrid;

        public void ExportDataGridToPdf(string filePath)
        {
            PdfDocument document = new PdfDocument();

            document.Info.Title = "Отчет";

            PdfPage page = document.AddPage();
            page.Size = PdfSharpCore.PageSize.A4;

            XGraphics gfx = XGraphics.FromPdfPage(page);

            XFont fontHeader = new XFont("Verdana", 12, XFontStyle.Bold);
            XFont fontData = new XFont("Verdana", 10, XFontStyle.Regular);

            double x = 40, y = 40;
            double cellHeight = 15, cellWidth = 100;

            foreach (var column in dataGrid.Columns)
            {
                gfx.DrawRectangle(XPens.Black, XBrushes.LightGray, x, y, cellWidth, cellHeight);
                gfx.DrawString(column.Header.ToString(), fontHeader, XBrushes.Black, new XRect(x, y, cellWidth, cellHeight), XStringFormats.Center);
                x += cellWidth;
            }

            x = 40;
            y += cellHeight;

            foreach (var item in dataGrid.Items)
            {
                x = 40;
                foreach (var column in dataGrid.Columns)
                {
                    var cellContent = column.GetCellContent(item) as TextBlock;
                    string cellText = cellContent?.Text ?? string.Empty;

                    gfx.DrawRectangle(XPens.Black, XBrushes.White, x, y, cellWidth, cellHeight);
                    gfx.DrawString(cellText, fontData, XBrushes.Black, new XRect(x, y, cellWidth, cellHeight), XStringFormats.Center);
                    x += cellWidth;
                }
                y += cellHeight;

                if (y + cellHeight > page.Height - 40)
                {
                    page = document.AddPage();
                    gfx.Dispose();
                    gfx = XGraphics.FromPdfPage(page);
                    y = 40;
                }
            }

            gfx.Dispose();

            using (var output = File.Create(filePath))
            {
                document.Save(output);
            }

            System.Diagnostics.Process.Start("explorer", filePath);
        }

        public void ExportToHtml(string filePath)
        {
            var sb = new StringBuilder();

            sb.Append("<html><body><table border='1'>");

            sb.Append("<tr>");
            foreach (var column in dataGrid.Columns)
                sb.Append($"<th>{column.Header}</th>");
            sb.Append("</tr>");

            foreach (var item in dataGrid.Items)
            {
                sb.Append("<tr>");
                foreach (var column in dataGrid.Columns)
                {
                    var cellValue = column.GetCellContent(item) as TextBlock;
                    sb.Append($"<td>{cellValue?.Text ?? string.Empty}</td>");
                }
                sb.Append("</tr>");
            }

            sb.Append("</table></body></html>");

            File.WriteAllText(filePath, sb.ToString());
        }
    }
}
