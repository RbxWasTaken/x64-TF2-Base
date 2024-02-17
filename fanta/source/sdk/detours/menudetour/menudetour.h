#pragma once
#include"../../../hooking/hooking.h"
#include"wnd_proc.h"
#include"../../../features/visuals/visuals.h"

inline std::string add_strings(std::string str1, std::string str2)
{
	return str1 + str2;
}

namespace Hooks
{
	namespace Menu
	{
		inline Hook::Manager Manger;
		namespace EndScene
		{
			typedef HRESULT(__stdcall* PresentFn)(LPDIRECT3DDEVICE9);
			PresentFn oPresent = 0;
			HRESULT __stdcall HkEndScene(LPDIRECT3DDEVICE9 pDevice)
			{
				if (!pOverlay.m_bInitImGui)
				{
					ImGui::CreateContext();
					pOverlay.InitStyle();
					pOverlay.InitFonts();
					ImGui_ImplWin32_Init(Process::hWindow);
					ImGui_ImplDX9_Init(pDevice);
					ImGui_ImplDX9_CreateDeviceObjects();
					ImGui::GetIO().ImeWindowHandle = Process::hWindow;
					Process::hWndProc = (WNDPROC)SetWindowLongPtr(Process::hWindow, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc::Detour);
					pOverlay.m_bInitImGui = true;
				}

				pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);
				pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
				pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
				pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);

				if (GetAsyncKeyState(VK_INSERT) & 0x1)
				{
					pHl2Interfaces.VGuiSurface->SetCursorAlwaysVisible(pOverlay.m_bRenderMenu = !pOverlay.m_bRenderMenu);
				}
				
				ImGui_ImplDX9_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();

				if (pOverlay.m_bRenderMenu==true)
				{
					pDraw.DimBackground(0, 0, ImColor(15, 15, 15, 50));
					
					ImGui::PushFont(pFonts.VerdanaSmall);
					ImGui::Begin("Sync.solutions", &vars::menu::close_button, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
					ImGui::SetWindowSize(ImVec2(795, 465));

					int height = 40;
					int width = 100;

					ImGui::Columns(2);
					ImGui::SetColumnOffset(1, width + 30);

					static OverlayTabs Tab = OverlayTabs::Visuals;
					{
						static ImVec4 InActive = ImVec4(0.09f, 0.09, 0.09f, 0.88f);
						static ImVec4 Active = ImVec4(0.0f, 0.5f, 0.5f, 0.9f);

						ImGui::Spacing();
						ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.f);
						ImGui::PushFont(pFonts.IconFont);

						ImGui::PushStyleColor(ImGuiCol_Button, Tab == OverlayTabs::Aimbot ? Active : InActive);
						if (ImGui::Button(add_strings(ICON_MD_SCORE, " Aimbot").c_str(), ImVec2(width, height)))
							Tab = OverlayTabs::Aimbot;

						ImGui::Spacing();
						ImGui::PushStyleColor(ImGuiCol_Button, Tab == OverlayTabs::Visuals ? Active : InActive);
						if (ImGui::Button(add_strings(ICON_MD_BRUSH, " Visuals").c_str(), ImVec2(width, height)))
							Tab = OverlayTabs::Visuals;

						ImGui::Spacing();
						ImGui::PushStyleColor(ImGuiCol_Button, Tab == OverlayTabs::Misc ? Active : InActive);
						if (ImGui::Button(add_strings(ICON_MD_MISCELLANEOUS_SERVICES, " Misc  ").c_str(), ImVec2(width, height)))
							Tab = OverlayTabs::Misc;

						ImGui::Spacing();
						ImGui::PushStyleColor(ImGuiCol_Button, Tab == OverlayTabs::Configs ? Active : InActive);
						if (ImGui::Button(add_strings(ICON_MD_GAMEPAD, " Configs").c_str(), ImVec2(width, height)))
							Tab = OverlayTabs::Configs;

						ImGui::PopFont();
						ImGui::PopStyleColor(4);
						ImGui::PopStyleVar(1);
					}

					ImGui::NextColumn();
					{
						switch (Tab)
						{
						case OverlayTabs::Aimbot:
							ImGui::Checkbox("Draw Fov", &vars::aimbot::draw_fov);
							ImGui::SliderFloat("Fov Scale", &vars::aimbot::fov_scale, 0.5, 360);
							break;
						case OverlayTabs::Visuals:
							ImGui::Checkbox("Flipviewmdoels", &vars::visuals::flip_viewmodels);
							ImGui::Checkbox("Weapon sway", &vars::visuals::weapon_sway);
							ImGui::Checkbox("Third Person", &vars::visuals::third_person);
							break;
						case OverlayTabs::Misc:
							break;
						case OverlayTabs::Configs:
							break;
						}
					}

					ImGui::PopFont();
					ImGui::End();
				}

				if (vars::menu::fps_window == true) { pVisuals.FpsWindow(); }
				if (vars::aimbot::draw_fov == true) 
				{
					int x = ImGui::GetIO().DisplaySize.x / 2;
					int y = ImGui::GetIO().DisplaySize.y / 2;
					pDraw.DrawCircle(x, y, &pColor.white, vars::aimbot::fov_scale);
				}
				if (vars::visuals::enable_visuals == true)
				{
					pVisuals.MainVisuals();
				}

				ImGui::EndFrame();
				ImGui::Render();
				ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
				pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, true);
				return oPresent(pDevice);
			}
		}

		DWORD __stdcall Initialize()
		{
			bool WndFocus = false;
			while (!WndFocus)
			{
				DWORD ProcID;
				GetWindowThreadProcessId(GetForegroundWindow(), &ProcID);
				if (GetCurrentProcessId() == ProcID)
				{
					Process::hProcId = GetCurrentProcessId();
					Process::hWindow = GetForegroundWindow();
					Process::hHandle = GetCurrentProcess();
					WndFocus = true;
				}
			}
			bool InitHook = false;
			while (!InitHook)
			{
				if (DirectX9::Init() == true) 
				{
					CreateHook(42, (void**)&EndScene::oPresent, EndScene::HkEndScene);
					InitHook = true;
				}
			}

			return 0;
		}
	}
}