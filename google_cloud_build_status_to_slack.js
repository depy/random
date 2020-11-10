const createSlackMessage = (build) => {
  var color = (build.status == "SUCCESS" ? "33FF33" : "FF3333");
  var successMsg = "Success";
  var failureMsg = "Failed";
  var statusMsg = (build.status == "SUCCESS" ? successMsg : failureMsg);
  var baseTxt = ":building_construction: *Google Cloud Build*"
  var emoji = (build.status == "SUCCESS" ? ":four_leaf_clover:" : ":octagonal_sign:");
  var txt = baseTxt + " " + emoji;
  var logUrlBase = "https://console.cloud.google.com/cloud-build/builds/";
  var logUrl = logUrlBase + build.id;
    
  const message = {
    text: txt,
    mrkdwn: true,
    attachments: [
      {
        color: color,
        fields: [
          {
            title: "Status",
            value: statusMsg,
            short: true
          },
          {
            title: "Repo",
            value: build.substitutions.REPO_NAME,
            short: true
          },
          {
            title: "Branch",
            value: build.substitutions.BRANCH_NAME,
            short: true
          },
          {
            title: "Commit",
            value: build.substitutions.SHORT_SHA,
            short: true
          }
        ],
        footer: "<" + build.logUrl + "|View logs here>"
      }
    ]
  };
  return message;
}