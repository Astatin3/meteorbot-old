package com.astatin3.meteorbot;

import com.astatin3.meteorbot.commands.CommandExample;
import com.astatin3.meteorbot.hud.HudExample;
import com.astatin3.meteorbot.modules.ModuleExample;
import com.mojang.logging.LogUtils;
import meteordevelopment.meteorclient.addons.MeteorAddon;
import meteordevelopment.meteorclient.commands.Commands;
import meteordevelopment.meteorclient.systems.hud.Hud;
import meteordevelopment.meteorclient.systems.hud.HudGroup;
import meteordevelopment.meteorclient.systems.modules.Category;
import meteordevelopment.meteorclient.systems.modules.Modules;
import org.slf4j.Logger;

public class Addon extends MeteorAddon {
    public static final Logger LOG = LogUtils.getLogger();
    public static final Category CATEGORY = new Category("MeteorBot");
    public static final HudGroup HUD_GROUP = new HudGroup("MeteorBot");

    @Override
    public void onInitialize() {
//        LOG.info("Initializing Meteor Addon Template");

        // Modules
        ModuleExample module = new ModuleExample();
        Modules.get().add(module);

        // Commands
        Commands.add(new CommandExample(module));

        // HUD
        Hud.get().register(HudExample.INFO);
    }

    @Override
    public void onRegisterCategories() {
        Modules.registerCategory(CATEGORY);
    }

    @Override
    public String getPackage() {
        return "com.astatin3.meteorbot";
    }
}
