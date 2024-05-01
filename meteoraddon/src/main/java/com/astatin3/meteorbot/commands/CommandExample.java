package com.astatin3.meteorbot.commands;

import com.astatin3.meteorbot.modules.ModuleExample;
import com.mojang.brigadier.arguments.StringArgumentType;
import com.mojang.brigadier.builder.LiteralArgumentBuilder;
import meteordevelopment.meteorclient.commands.Command;
import net.minecraft.command.CommandSource;

import static com.mojang.brigadier.Command.SINGLE_SUCCESS;

public class CommandExample extends Command {
    private ModuleExample module;

    public CommandExample(ModuleExample module) {
        super("mb", "Sends a message.");
        this.module = module;
    }

    private void printHelpInfo(){
        info("\n" +
            "-- Meteor Bot Help --\n" +
            "\n" +
            ".mb help                       - Print this help info\n" +
            ".mb chat <msg>                 - Send chat message\n" +
            ".mb cmd <cmd>                  - Send command (No '/')\n" +
            ".mb stop                       - Stop bot\n" +
            ".mb rawsend <type> <content>   - Send raw message to bot\n");
    }

    @Override
    public void build(LiteralArgumentBuilder<CommandSource> builder) {
        builder.executes(context -> {
            printHelpInfo();
            return SINGLE_SUCCESS;
        });

        builder.then(literal("help").executes(context -> {
            printHelpInfo();
            return SINGLE_SUCCESS;
        }));

        builder.then(literal("chat")
        .then(
        argument(
        "msg", StringArgumentType.greedyString())
        .executes(context -> {
            module.writeSTDIN("chat:" + context.getArgument("msg", String.class));
            return SINGLE_SUCCESS;
        })));

        builder.then(literal("cmd")
        .then(
        argument(
        "cmd", StringArgumentType.greedyString())
        .executes(context -> {
            module.writeSTDIN("cmd:" + context.getArgument("cmd", String.class));
            return SINGLE_SUCCESS;
        })));


        builder.then(literal("stop").executes(context -> {
            module.stopBot();
            return SINGLE_SUCCESS;
        }));


        builder.then(literal("rawsend")
        .then(
        argument(
        "type", StringArgumentType.string())
        .then(
        argument(
        "content", StringArgumentType.greedyString())
        .executes(context -> {
            module.writeSTDIN(context.getArgument("type", String.class) + ":" + context.getArgument("content", String.class));
            return SINGLE_SUCCESS;
        }))));

    }
}
