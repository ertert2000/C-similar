using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

/*Задание 7. Разработать ПК для администратора футбольной команды. В
ПК должна храниться информация об игроках команды, календарь и
результаты игр. Администратор футбольной команды может добавлять,
изменять и удалять эту информацию. Ему могут потребоваться следующие
сведения:
 список футболистов и их специализация;
 календарь игр;
 количество проведенных игр;
 отчета о результативности каждого игрока команды.
*/



namespace lib2
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            DataContext = new MainViewModel(this);
        }

        
    }
}