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
            List<FootballPlayer> people = new List<FootballPlayer>
            {
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист"),
                new FootballPlayer ("Иван", "524", "Программист")
            };

            fotbal.ItemsSource = people;
            DataContext = new ControlButtonsViewModel(this);
        }
    }
}



/*<Style TargetType="DataGrid">
            <Setter Property="Background" Value="#444444" />
            <!-- Темный фон -->
            <Setter Property="Foreground" Value="White" />
            <Setter Property="FontSize" Value="14" />
            <Setter Property="RowHeight" Value="30" />
            <Setter Property="AlternatingRowBackground" Value="Aqua" />
            <Setter Property="AutoGenerateColumns" Value="True" />
            <Setter Property="BorderBrush" Value="Transparent" />
            <Setter Property="BorderThickness" Value="1" />
            <Setter Property="ScrollViewer.CanContentScroll" Value="True" />
            <Setter Property="ScrollViewer.VerticalScrollBarVisibility" Value="Auto" />
            <Setter Property="ScrollViewer.HorizontalScrollBarVisibility" Value="Auto" />
            <Setter Property="CellStyle">
                <Setter.Value>
                    <Style TargetType="DataGridCell">
                        <Setter Property="Padding" Value="10" />
                        <Setter Property="BorderBrush" Value="Aqua" />
                        <Setter Property="BorderThickness" Value="0" />
                        <Setter Property="Background" Value="Transparent" />
                        <Setter Property="Foreground" Value="White" />
                        <Setter Property="FontWeight" Value="Normal" />
                        <Style.Triggers>
                            <Trigger Property="IsSelected" Value="True">
                                <Setter Property="Background" Value="#333333" />
                                <Setter Property="Foreground" Value="#FFFFFF" />
                            </Trigger>
                        </Style.Triggers>
                    </Style>
                </Setter.Value>
            </Setter>
            <Setter Property="RowStyle">
                <Setter.Value>
                    <Style TargetType="DataGridRow">
                        <Setter Property="Background" Value="Transparent" />
                        <Setter Property="Foreground" Value="White" />
                        <Style.Triggers>
                            <Trigger Property="IsMouseOver" Value="True">
                                <Setter Property="Background" Value="#333333" />
                            </Trigger>
                            <Trigger Property="IsSelected" Value="True">
                                <Setter Property="Background" Value="#333333" />
                                <Setter Property="Foreground" Value="#FFFFFF" />
                            </Trigger>
                        </Style.Triggers>
                    </Style>
                </Setter.Value>
            </Setter>

            <Setter Property="ColumnHeaderStyle">
                <Setter.Value>
                    <Style TargetType="DataGridColumnHeader">
                        <Setter Property="Background" Value="#444444" />
                        <Setter Property="Foreground" Value="White" />
                        <Setter Property="FontWeight" Value="Bold" />
                        <Setter Property="Padding" Value="10" />
                        <Setter Property="BorderBrush" Value="Transparent" />
                        <Setter Property="BorderThickness" Value="0" />
                        <Style.Triggers>
                            <Trigger Property="IsMouseOver" Value="True">
                                <Setter Property="Background" Value="#555555" />
                            </Trigger>
                        </Style.Triggers>
                    </Style>
                </Setter.Value>
            </Setter>
        </Style>

        <Style TargetType="ScrollBar">
            <Setter Property="Background" Value="Transparent" />
            <Setter Property="Width" Value="16" />
            <Setter Property="Template">
                <Setter.Value>
                    <ControlTemplate TargetType="ScrollBar">
                        <Grid Background="Transparent">
                            <Track Name="PART_Track" IsDirectionReversed="True" >
                                <Track.Thumb>
                                    <Thumb Background="#444444" Height="50" Margin="0">
                                        <Thumb.Template>
                                            <ControlTemplate TargetType="Thumb">
                                                <Border Background="{TemplateBinding Background}" CornerRadius="8"/>
                                            </ControlTemplate>
                                        </Thumb.Template>
                                    </Thumb>
                                </Track.Thumb>
                            </Track>
                        </Grid>
                    </ControlTemplate>
                </Setter.Value>
            </Setter>
        </Style>

        <Style TargetType="ScrollViewer">
            <Setter Property="VerticalScrollBarVisibility" Value="Auto" />
            <Setter Property="VerticalAlignment" Value="Top" />
            <Setter Property="Background" Value="Transparent" />
        </Style>*/