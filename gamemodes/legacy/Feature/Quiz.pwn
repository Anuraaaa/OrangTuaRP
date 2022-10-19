
enum E_QUIZ_DATA {
    bool:quizReady,
    quizAnswer[128],
    quizQuest[128]
};
new QuizData[E_QUIZ_DATA];

CMD:quiz(playerid, params[])
{
    new choice[10], subparam[128];
    if(sscanf(params, "s[10]S()[128]", choice, subparam))
        return SendSyntaxMessage(playerid, "/quiz [create/answer/end]");

    if(!strcmp(choice, "create"))
    {
        if (PlayerData[playerid][pAdmin] < 1)
            return PermissionError(playerid);

        new quest[128], answer[128];
        if(QuizData[quizReady])
            return SendErrorMessage(playerid, "You can't create more than 1 quiz.");

        if(sscanf(subparam, "p<:>s[128]s[128]", quest,answer))
            return SendSyntaxMessage(playerid, "/quiz create [questions] : [answer]");

        QuizData[quizReady] = true;
        format(QuizData[quizQuest], 128, quest);
        format(QuizData[quizAnswer], 128, answer);

        SendClientMessageToAllEx(X11_LIGHTBLUE, "QUIZ: "WHITE"%s", quest);
        SendClientMessageToAll(X11_LIGHTBLUE, "QUIZ: "WHITE"Use '"YELLOW"/quiz answer"WHITE"' to answer the quiz.");
        SendAdminMessage(X11_TOMATO_1, "AdmCmd: %s has initiated a quiz.", GetUsername(playerid));
    }
    else if(!strcmp(choice, "answer"))
    {
        new answered[128];

        if(sscanf(subparam,"s[128]", answered))
        return SendSyntaxMessage(playerid, "/quiz answer [answer]");

        if(!QuizData[quizReady])
        return SendErrorMessage(playerid, "There is no available quiz.");

        if(!strcmp(answered, QuizData[quizAnswer], true))
        {
            SendClientMessageToAllEx(X11_LIGHTBLUE, "QUIZ: "YELLOW"%s(%d) "WHITE"won the quiz with answer: '"YELLOW"%s"WHITE"'",GetName(playerid, false), playerid, QuizData[quizAnswer]);

            QuizData[quizReady] = false;
        }
        else
            SendErrorMessage(playerid, "You have inputted wrong answer.");
    }
    else if(!strcmp(choice, "end"))
    {

        if (PlayerData[playerid][pAdmin] < 1)
            return PermissionError(playerid);

        if(!QuizData[quizAnswer])
        return SendErrorMessage(playerid, "There is no available quiz.");

        SendClientMessageToAllEx(X11_LIGHTBLUE, "QUIZ"WHITE": Admin "YELLOW"%s"WHITE" ended the quiz. The answer is '"YELLOW"%s"WHITE"'", GetUsername(playerid), QuizData[quizAnswer]);
        QuizData[quizReady] = false;

    }
    else return SendSyntaxMessage(playerid,  "/quiz [create/answer/end]");
    return 1;
}