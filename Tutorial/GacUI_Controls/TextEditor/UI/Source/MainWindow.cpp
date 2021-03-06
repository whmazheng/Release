﻿/***********************************************************************
!!!!!! DO NOT MODIFY !!!!!!

GacGen.exe Resource.xml

This file is generated by Workflow compiler
https://github.com/vczh-libraries
***********************************************************************/

#include "Demo.h"
/* CodePack:BeginIgnore() */
#ifndef VCZH_DEBUG_NO_REFLECTION
/* CodePack:ConditionOff(VCZH_DEBUG_NO_REFLECTION, DemoReflection.h) */
#include "DemoReflection.h"
#endif
/* CodePack:EndIgnore() */

#if defined( _MSC_VER)
#pragma warning(push)
#pragma warning(disable:4250)
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses-equality"
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wparentheses-equality"
#endif

#define GLOBAL_SYMBOL ::vl_workflow_global::Demo::
#define GLOBAL_NAME ::vl_workflow_global::Demo::Instance().
#define GLOBAL_OBJ &::vl_workflow_global::Demo::Instance()
#define USERIMPL(...)

/***********************************************************************
Class (::demo::MainWindow)
***********************************************************************/

namespace demo
{
	USERIMPL(/* ::demo::MainWindow */)
	bool MainWindow::CanCloseFile()
	{
		if (textBox->GetModified())
		{
			switch (dialogQueryClose->ShowDialog())
			{
			case INativeDialogService::MessageBoxButtonsOutput::SelectYes:
				return SaveFile(false);
			case INativeDialogService::MessageBoxButtonsOutput::SelectNo:
				return true;
			default:
				return false;
			}
		}
		else
		{
			return true;
		}
	}

	USERIMPL(/* ::demo::MainWindow */)
	bool MainWindow::OpenFile(::vl::vint filterIndex)
	{
		if (CanCloseFile())
		{
			dialogOpen->SetFilterIndex(filterIndex);
			if (dialogOpen->ShowDialog())
			{
				stream::FileStream fileStream(dialogOpen->GetFileName(), stream::FileStream::ReadOnly);
				if (fileStream.IsAvailable())
				{
					stream::BomDecoder decoder;
					stream::DecoderStream decoderStream(fileStream, decoder);
					stream::StreamReader reader(decoderStream);
					textBox->SetText(reader.ReadToEnd());
					textBox->Select(TextPos(), TextPos());
					textBox->SetFocus();
					textBox->ClearUndoRedo();

					fileName = dialogOpen->GetFileName();
					if (INVLOC.EndsWith(fileName, L".xml", Locale::IgnoreCase))
					{
						SetupXmlConfig();
					}
					else
					{
						SetupTextConfig();
					}
					return true;
				}
				else
				{
					dialogCannotOpen->ShowDialog();
				}
			}
		}
		return false;
	}

	USERIMPL(/* ::demo::MainWindow */)
	bool MainWindow::SaveFile(bool saveAs)
	{
		WString targetFileName = fileName;
		if (saveAs || targetFileName == L"")
		{
			dialogSave->SetFilterIndex(isXml ? 1 : 0);
			if (dialogSave->ShowDialog())
			{
				targetFileName = dialogSave->GetFileName();
			}
			else
			{
				return false;
			}
		}

		stream::FileStream fileStream(targetFileName, stream::FileStream::WriteOnly);
		if (fileStream.IsAvailable())
		{
			stream::BomEncoder encoder(stream::BomEncoder::Utf16);
			stream::EncoderStream encoderStream(fileStream, encoder);
			stream::StreamWriter writer(encoderStream);
			writer.WriteString(textBox->GetText());
			textBox->NotifyModificationSaved();

			fileName = targetFileName;
			if (INVLOC.EndsWith(fileName, L".xml", Locale::IgnoreCase))
			{
				SetupXmlConfig();
			}
			else
			{
				SetupTextConfig();
			}
			return true;
		}
		else
		{
			dialogCannotSave->ShowDialog();
		}
		return false;
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::SetupTextConfig()
	{
		if (isXml == true)
		{
			isXml = false;
			SetColorizer(textBox, false);
		}
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::SetupXmlConfig()
	{
		if (isXml == false)
		{
			isXml = true;
			SetColorizer(textBox, true);
		}
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::commandFileNewText_Executed(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments)
	{
		if (CanCloseFile())
		{
			textBox->SetText(L"");
			textBox->ClearUndoRedo();
			SetupTextConfig();
		}
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::commandFileNewXml_Executed(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments)
	{
		if (CanCloseFile())
		{
			textBox->SetText(L"");
			textBox->ClearUndoRedo();
			SetupXmlConfig();
		}
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::commandFileOpen_Executed(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments)
	{
		OpenFile(dialogOpen->GetFilterIndex());
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::commandFileOpenText_Executed(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments)
	{
		OpenFile(0);
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::commandFileOpenXml_Executed(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments)
	{
		OpenFile(1);
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::commandFileSave_Executed(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments)
	{
		SaveFile(false);
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::commandFileSaveAs_Executed(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments)
	{
		SaveFile(true);
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::commandFileExit_Executed(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments)
	{
		Close();
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::commandEditUndo_Executed(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments)
	{
		textBox->Undo();
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::commandEditRedo_Executed(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments)
	{
		textBox->Redo();
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::commandEditCut_Executed(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments)
	{
		textBox->Cut();
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::commandEditCopy_Executed(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments)
	{
		textBox->Copy();
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::commandEditPaste_Executed(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments)
	{
		textBox->Paste();
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::commandEditDelete_Executed(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments)
	{
		textBox->SetSelectionText(L"");
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::commandEditSelect_Executed(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments)
	{
		textBox->SelectAll();
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::commandEditFind_Executed(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments)
	{
		if (!findWindow)
		{
			auto window = MakePtr<FindWindow>();
			window->textBox = textBox;
			window->MoveToScreenCenter();
			window->GetNativeWindow()->SetParent(GetNativeWindow());
			findWindow = window;
		}
		findWindow->Show();
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::commandAbout_Executed(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments)
	{
		auto window = new AboutWindow;
		window->MoveToScreenCenter();
		window->ShowModalAndDelete(this, []() {});
	}

	USERIMPL(/* ::demo::MainWindow */)
	void MainWindow::window_Closing(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiRequestEventArgs* arguments)
	{
		arguments->cancel = !CanCloseFile();
	}

	MainWindow::MainWindow()
		: ::vl::presentation::controls::GuiWindow(::vl::__vwsn::This(::vl::presentation::theme::GetCurrentTheme())->CreateWindowStyle())
	{
		auto __vwsn_resource_ = ::vl::__vwsn::This(::vl::presentation::GetResourceManager())->GetResourceFromClassName(::vl::WString(L"demo::MainWindow", false));
		auto __vwsn_resolver_ = ::vl::Ptr<::vl::presentation::GuiResourcePathResolver>(new ::vl::presentation::GuiResourcePathResolver(__vwsn_resource_, ::vl::__vwsn::This(__vwsn_resource_.Obj())->GetWorkingDirectory()));
		::vl::__vwsn::This(this)->SetResourceResolver(__vwsn_resolver_);
		::vl::__vwsn::This(this)->__vwsn_initialize_instance_(this);
	}

	MainWindow::~MainWindow()
	{
		this->FinalizeInstanceRecursively(static_cast<::vl::presentation::controls::GuiControlHost*>(this));
	}

}
#undef GLOBAL_SYMBOL
#undef GLOBAL_NAME
#undef GLOBAL_OBJ
#undef USERIMPL

#if defined( _MSC_VER)
#pragma warning(pop)
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
