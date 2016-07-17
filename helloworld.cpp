//$Id: helloworld.cc 836 2007-05-09 03:02:38Z jjongsma $ -*- c++ -*-

/* gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "helloworld.h"
#include <iostream>
#include <vector>
using namespace std;

HelloWorld::HelloWorld()
: m_button("Hello World"),   // creates a new button with label "Hello World".
  m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Button_Quit("Fechar")
{
  // Sets the border width of the window.
  set_border_width(10);
  set_title("Visualizador de logs");
  set_default_size(largura, altura);

  add_arquivo.set_label("Adicionar arquivo");
  remover_aba.set_label("Remover Aba");


  // --
  // Gtk::TreeView *treeview = Gtk::manage(new Gtk::TreeView);
  //   treeview.set_hexpand(true);
  //   treeview.set_vexpand(true);
  //
  // refTreeModel = Gtk::ListStore::create(columns);
  //   treeview.set_model(refTreeModel);
  //   treeview.append_column("Cnt", columns.col_cnt);
  //   treeview.append_column("Text", columns.col_text);
  //   add_lista("teste 1");
  //   add_lista("teste 2");
  // add_lista_em_aba();
  // add_lista_em_aba();
  // --


  add(m_VBox);

 //Add the Notebook, with the button underneath:
 m_Notebook.set_border_width(10);
 m_VBox.pack_start(m_Notebook);
 m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

 m_ButtonBox.pack_start(add_arquivo, Gtk::PACK_SHRINK);
 m_ButtonBox.pack_start(remover_aba, Gtk::PACK_SHRINK);
 m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);

 m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
             &HelloWorld::on_button_quit) );

 add_arquivo.signal_clicked().connect(sigc::mem_fun(*this,
             &HelloWorld::evento_botao_add_arquivo) );

 remover_aba.signal_clicked().connect(sigc::mem_fun(*this,
             &HelloWorld::evento_botao_remover_aba) );


 //Add the Notebook pages:
 // add_aba("Primeiro");

 m_Notebook.signal_switch_page().connect(sigc::mem_fun(*this,
             &HelloWorld::on_notebook_switch_page) );

 show_all_children();

}

HelloWorld::~HelloWorld()
{
}

void HelloWorld::on_button_clicked()
{
  std::cout << "Hello World" << std::endl;
}

void HelloWorld::evento_botao_add_arquivo()
{
  // add_aba("xip");
  std::cout << "Add um novo arquivo" << std::endl;

  abrir_seletor_de_arquivos();
  if( (!caminho_completo_arquivo.empty()) && (!nome_arquivo.empty()) )
  {
    std::cout << "File selected: " <<  caminho_completo_arquivo << std::endl;
    vector<Glib::ustring> linhas = linhas_arquivo(caminho_completo_arquivo);

    int tam_max = 30;
    if( nome_arquivo.size() > tam_max ){
      nome_arquivo = nome_arquivo.substr(0,tam_max-3)+"...";
    }
    add_aba(nome_arquivo, &linhas);
  }

}

void HelloWorld::evento_botao_remover_aba()
{
  int aba = m_Notebook.get_current_page();
  std::cout << "remover aba: " << aba << std::endl;
  if( m_Notebook.get_n_pages() > 1 ){
    m_Notebook.remove_page(aba);
  }
}

void HelloWorld::on_button_quit()
{
  hide();
}

void HelloWorld::on_notebook_switch_page(Gtk::Widget* /* page */, guint page_num)
{
  std::cout << "Switched to tab with index " << page_num << std::endl;
  //You can also use m_Notebook.get_current_page() to get this index.
}

void HelloWorld::add_aba(Glib::ustring titulo_da_aba, vector<Glib::ustring>* linhas)
{
  int indice_nova_aba = m_Notebook.get_n_pages();

  // if( linhas->empty() )
  // {
  //     // vector<Glib::ustring> linhas;
  //     for(int i=0; i<100; i++){
  //       linhas->push_back("item ");
  //     }
  // }

  add_lista_em_aba(indice_nova_aba, *linhas);
  m_Notebook.append_page(scroll[indice_nova_aba], titulo_da_aba);
  lista.show_all();
  show_all_children();
  m_Notebook.set_current_page(indice_nova_aba);
}

void HelloWorld::abrir_seletor_de_arquivos()
{
  Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
  dialog.set_transient_for(*this);

  //Add response buttons the the dialog:
  dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  dialog.add_button("_Open", Gtk::RESPONSE_OK);

  //Add filters, so that only certain file types can be selected:
  // auto filter_text = Gtk::FileFilter::create();
  // filter_text->set_name("Text files");
  // filter_text->add_mime_type("text/plain");
  // dialog.add_filter(filter_text);
  //
  // auto filter_cpp = Gtk::FileFilter::create();
  // filter_cpp->set_name("C/C++ files");
  // filter_cpp->add_mime_type("text/x-c");
  // filter_cpp->add_mime_type("text/x-c++");
  // filter_cpp->add_mime_type("text/x-c-header");
  // dialog.add_filter(filter_cpp);

  auto filter_any = Gtk::FileFilter::create();
  filter_any->set_name("Any files");
  filter_any->add_pattern("*");
  dialog.add_filter(filter_any);

  //Show the dialog and wait for a user response:
  int result = dialog.run();

  //Handle the response:
  std::string filename = "";
  switch(result)
  {
      case(Gtk::RESPONSE_OK):
      {
        std::cout << "Open clicked." << std::endl;

        auto arq = dialog.get_file();
        nome_arquivo = arq->get_basename();

        //Notice that this is a std::string, not a Glib::ustring.
        filename = dialog.get_filename();
        caminho_completo_arquivo = filename;
        break;
      }
      case(Gtk::RESPONSE_CANCEL):
      {
        std::cout << "Cancel clicked." << std::endl;
        break;
      }
      default:
      {
        std::cout << "Unexpected button clicked." << std::endl;
        break;
      }
  }
}

vector<Glib::ustring> HelloWorld::linhas_arquivo(std::string& arquivo)
{
    std::ifstream file(arquivo);
    std::string str;
    vector<Glib::ustring> linhas;
    while (std::getline(file, str))
    {
      linhas.push_back(str);
    }
    return linhas;
}
