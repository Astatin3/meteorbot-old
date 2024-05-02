package com.astatin3.meteorbot.modules;

import com.astatin3.meteorbot.Addon;
import meteordevelopment.meteorclient.settings.BoolSetting;
import meteordevelopment.meteorclient.settings.Setting;
import meteordevelopment.meteorclient.settings.SettingGroup;
import meteordevelopment.meteorclient.settings.StringSetting;
import meteordevelopment.meteorclient.systems.modules.Module;
import net.minecraft.util.math.Vec3d;

import java.io.*;
import java.util.concurrent.TimeUnit;


public class ModuleExample extends Module {
    public ModuleExample() {
        super(Addon.CATEGORY, "Meteor-Bot", "An example module in a custom category.");
    }

    private final SettingGroup sgGeneral = settings.getDefaultGroup();

    private final Setting<String> botpath = sgGeneral.add(new StringSetting.Builder()
        .name("Path")
        .description("The location of the bot executable")
        .defaultValue("/home/astatin3/Documents/GitHub/meteorbot/bot/cmake-build-debug/bin/McConnectBot")
        .visible(() -> true)
        .build()
    );

    private final Setting<Boolean> verboseMode = sgGeneral.add(new BoolSetting.Builder()
        .name("Verbose")
        .description("Enable verbose output")
        .defaultValue(true)
        .visible(() -> true)
        .build()
    );

    private Process process;
    private BufferedOutputStream stdin;

    private void startCMD(){
        if(!new File(botpath.get()).exists()){
            info("Executable " + botpath.get() + " does not exist!");
            return;
        }

        try {
            process = Runtime.getRuntime().exec(botpath.get());
            stdin = new BufferedOutputStream(process.getOutputStream());
//            pipedInputStream = new PipedInputStream(stdin);

        } catch (IOException e) {
            throw new RuntimeException(e);
        } catch (Exception e){
            info("Starting " + botpath.get() + " Failed! (" + e + ")");
            e.printStackTrace();
        }

        cmdThread = new Thread(new Runnable() {
            public void run() {
                readCMD();
                quitBot();
            }
        });
        cmdThread.start();
    }

    private void readCMD(){

//        ProcessBuilder processBuilder = new ProcessBuilder(args);
//        processBuilder.redirectErrorStream(true);

        try {
//            Process process = processBuilder.start();
            BufferedReader stdout = new BufferedReader(new InputStreamReader(process.getInputStream()));

            String line;
            while ((line = stdout.readLine()) != null) {
                parseSTDOUT(line);
            }

            int exitCode = process.waitFor();

            if(verboseMode.get())
                info("Program exited with code: " + exitCode);

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void parseSTDOUT(String str){
        if(verboseMode.get())
            info(str);

        if(str.equals("Get Player Pos")){
            assert mc.player != null;
            Vec3d vel = mc.player.getVelocity();
            writeSTDIN("PlayerPos:" +
                mc.player.getX() + "," +
                mc.player.getY() + "," +
                mc.player.getZ() + "," +
                vel.getX() + "," +
                vel.getZ() + "," +
                vel.getZ() + ",");
        }
    }

    private Thread cmdThread = null;

    public void onActivate() {
        quitBot();
        startCMD();
    }

    @Override
    public void onDeactivate() {
        quitBot();
    }

    public void quitBot(){
        if (cmdThread != null) {
            writeSTDIN("Disconnect");
            cmdThread.interrupt();
            process = null;
            stdin = null;
            cmdThread = null;
        }
    }

    public void writeSTDIN(String line) {
        if(cmdThread == null){
            info("Bot program is not running...");
            return;
        }

        if(process == null || stdin == null){
            info("Bot is still initializing...");
            return;
        }


        try {
            stdin.write((line + "\n").getBytes());
            stdin.flush();
            if(verboseMode.get())
                info("Sent: " + line);
        } catch (IOException e) {
            info(e.toString());
        }
    }

    public boolean followMode = false;
    public void startFollowMode(){
        writeSTDIN("startGotoSteamMode");
        followMode = true;
        new Thread(new Runnable() {
            public void run() {
                while(followMode){
                    writeSTDIN("goto:"+mc.player.getX()+","+mc.player.getY()+","+mc.player.getZ());
                    try {
                        TimeUnit.SECONDS.sleep(1);
                    } catch (InterruptedException ie) {
                        Thread.currentThread().interrupt();
                    }
                }
            }
        }).start();
    }
}

